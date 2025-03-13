#include <Arduino.h>
#include "ros.h"
// #include <message_pkg/Vel_msg.h>
#include <geometry_msgs/Twist.h>
#include "param_config.h"
#include "pin_config.h"
#include "main.h"
// #include <util/atomic.h>
#include <std_msgs/Int32.h>
#include <HardwareSerial.h>
#include <stdint.h>

// uart pin 
HardwareSerial SerialPort1(1);  // UART1
HardwareSerial SerialPort2(2);  // UART2

// message_pkg::Vel_msg vel_info;
ros::NodeHandle nh;
ESP32_Controller* Main_ctrl;
Robot myrobot;

#define RXD1 4   // GPIO pin for UART1 RX (Receive)  - D5 of STM
#define TXD1 5   // GPIO pin for UART1 TX (Transmit)

#define RXD2 16  // GPIO pin for UART2 RX (Receive)
#define TXD2 17  // GPIO pin for UART2 TX (Transmit) - D6 of STM


// variables
int w_r=0, w_l=0;
double speed_ang=0, speed_lin=0;
double wheel_rad = 0.0325, wheel_sep = 0.295;

long tim = 0;

// globals
long prevT = 0;
int posPrev_left = 0;
int posPrev_right = 0;

// Use the "volatile" directive for variables
// used in an interrupt
volatile int32_t pos_left = 0;
volatile int32_t pos_right = 0;
volatile float velocity_i = 0;
volatile long prevT_i = 0;

float vFilt_left = 0;
float vPrev_left = 0;
float vFilt_right = 0;
float vPrev_right = 0;

float eintegral_r = 0;
float eintegral_l = 0;

// time pub data 
long currentMillis = 0;
const int interval = 30;
long previousMillis = 0;

// send data
int bit_rs = 0;
float linear_x = 0.17;
float ang_z = 0.15;
int sendData; 
String message;

//receive data
String receivedData = "";
bool dataReady = false;
int data1;
int data2;
bool is_recv_vel = false;

void messageCb(const geometry_msgs::Twist& msg){
   is_recv_vel = true;

   speed_ang = msg.angular.z;
   speed_lin = msg.linear.x;
   linear_x = abs(speed_lin);
   ang_z = abs(speed_ang);

   if (speed_ang > 0 and speed_lin == 0){   // turn right
      bit_rs = 4;
   }
   else if(speed_ang < 0 and speed_lin == 0){  // turn left
      bit_rs = 3;
   }
   else if(speed_ang == 0 and speed_lin > 0){  // go straight
      bit_rs = 1;
   }
   else if(speed_ang == 0 and speed_lin < 0){  // go behind
      bit_rs = 2;
   }
   else if(speed_ang == 0 and speed_lin == 0){  // stop
      bit_rs = 0;
   }
   else{
      bit_rs = 0;
   }
   
} 

std_msgs::Int32 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);
 
std_msgs::Int32 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &messageCb);

void setup()
{  

   // setup for ROS communication
   nh.initNode();
   nh.getHardware()->setBaud(57600);
   nh.subscribe(sub);
   // nh.advertise(pwm_info);
   nh.advertise(rightPub);
   nh.advertise(leftPub);

   // setup Uart communication
   // Serial.begin(115200);
   SerialPort1.begin(115200, SERIAL_8N1, RXD1, TXD1);
   SerialPort2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}

void loop()
{  

   // send cmd_vel command
   if(is_recv_vel == true){
      sendData = bit_rs*1000000 + linear_x*1000000 + ang_z*1000;
      // Serial.println("send data: " + sendData);
      message = "DATA:" + String(sendData) + "\n";  // Đóng gói dữ liệu int vào chuỗi
      SerialPort2.print(message);  // Gửi chuỗi qua UART
      is_recv_vel = false;
   }

   // receive and sendata from encoder to ros
   if (SerialPort1.available()) {
      receivedData = SerialPort1.readStringUntil('\n');
      // receivedData.trim();
      Serial.println("Received data: " + receivedData);

      // Serial.print("Length of string: ");
      // Serial.println(receivedData.length());

      // // Tách chuỗi dựa vào dấu phẩy ','
      int commaIndex = receivedData.indexOf(',');
      // Serial.print("Comma index: ");
      // Serial.println(commaIndex);  // In vị trí của dấu
      
      if (commaIndex != -1) {
         // Lấy phần trước dấu phẩy
         String data1_str = receivedData.substring(0, commaIndex);
         int32_t data1 = data1_str.toInt();  // Chuyển chuỗi thành số nguyên
         // Serial.print("Data1: ");
         // Serial.println(data1);
         left_wheel_tick_count.data = data1;

         // Lấy phần sau dấu phẩy
         String data2_str = receivedData.substring(commaIndex + 1);
         int32_t data2 = data2_str.toInt();  // Chuyển chuỗi thành số nguyên
         // Serial.print("Data2: ");
         // Serial.println(data2);
         right_wheel_tick_count.data = data2;
      }
   }

   // publish encoder data
   currentMillis = millis();
   
   // If the time interval has passed, publish the number of ticks,
   // and calculate the velocities.
   if (currentMillis - previousMillis > interval) {
      
      previousMillis = currentMillis;
   
      // Publish tick counts to topics
      leftPub.publish( &left_wheel_tick_count );
      rightPub.publish( &right_wheel_tick_count );
      
   }
   nh.spinOnce();
}

