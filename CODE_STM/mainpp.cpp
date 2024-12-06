#include <mainpp.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include "Motor.h"
ros::NodeHandle nh;

volatile long pos_left = 0;
volatile long pos_right = 0;

int Direction_left = 1;
int Direction_right = 1;

const int encoder_minimum = -32768;
const int encoder_maximum = 32767;

const int interval = 30;
long previousMillis = 0;
long currentMillis = 0;

std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);

std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

const int PWM_INCREMENT = 1;
const int TICKS_PER_REVOLUTION = 800;
const double WHEEL_RADIUS = 0.0325;
const double WHEEL_BASE = 0.27;
const double TICKS_PER_METER = 3920;
const int K_P = 278;
const int b = 52;
const int DRIFT_MULTIPLIER = 120;
const int PWM_TURN = 200;
const int PWM_MIN = 100;
const int PWM_MAX = 255;

double velLeftWheel = 0;
double velRightWheel = 0;
double pwmLeftReq = 0;
double pwmRightReq = 0;

double lastCmdVelReceived = 0;

int bit_rs = 0;
double speed_ang=0, speed_lin=0;

void USARTx_IRQHandler() {
    nh.getHardware()->flush();
}

void USARTx_RX_IRQHandler() {
    nh.getHardware()->reset_rbuf();
}

extern void EXTI9_5_IRQHandler(void);

extern void EXTI15_10_IRQHandler(void);

void calc_vel_left_wheel() {
    static double prevTime = 0;
    static int prevLeftCount = 0;

    int numOfTicks = (65535 + left_wheel_tick_count.data - prevLeftCount) % 65535;
    if (numOfTicks > 10000) {
        numOfTicks = 0 - (65535 - numOfTicks);
    }

    velLeftWheel = numOfTicks / TICKS_PER_METER / ((SysTick->VAL / 1000) - prevTime);
    prevLeftCount = left_wheel_tick_count.data;
    prevTime = (SysTick->VAL / 1000);
}

void calc_vel_right_wheel() {
    static double prevTime = 0;
    static int prevRightCount = 0;

    int numOfTicks = (65535 + right_wheel_tick_count.data - prevRightCount) % 65535;
    if (numOfTicks > 10000) {
        numOfTicks = 0 - (65535 - numOfTicks);
    }

    velRightWheel = numOfTicks / TICKS_PER_METER / ((SysTick->VAL / 1000) - prevTime);
    prevRightCount = right_wheel_tick_count.data;
    prevTime = (SysTick->VAL / 1000);
}

extern void robot_forward(int32_t pwm1, int32_t pwm2) ;
extern void robot_backward(int32_t pwm1, int32_t pwm2);

extern void robot_turnleft(int32_t pwm1, int32_t pwm2);
extern void robot_turnright(int32_t pwm1, int32_t pwm2);
extern void robot_stop() ;

void calc_pwm_values(const geometry_msgs::Twist& cmdVel) {
    lastCmdVelReceived = (SysTick->VAL / 1000);

    speed_ang = cmdVel.angular.z;
    speed_lin = cmdVel.linear.x;

    if (speed_ang > 0 && speed_lin == 0) {
        bit_rs = 4;
    } else if (speed_ang < 0 && speed_lin == 0) {
        bit_rs = 3;
    } else if (speed_ang == 0 && speed_lin > 0) {
        bit_rs = 1;
    } else if (speed_ang == 0 && speed_lin < 0) {
        bit_rs = 2;
    } else if (speed_ang == 0 && speed_lin == 0) {
        bit_rs = 0;
    } else {
        bit_rs = 0;
    }
}

void set_pwm_values() {
	switch (bit_rs){
		case 0:
				ModeMotor(Stop,0,0);
		break;
		case 1:			
					ModeMotor(Forward, 66534, 66534);	
		break;
		case 2:
				ModeMotor(Backward, 66534, 66534);
		break;
		case 3:
				ModeMotor(Left, 20000, 20000);
		break;
		case 4: 
				ModeMotor(Right, 20000, 20000); 
		break;
		default :
			break;
	}
  // if (bit_rs == 0) 
//            ModeMotor(Stop, 0, 0); 
//        else if (bit_rs == 1) 
//            ModeMotor(Forward, 66534, 66534); 
//        else if (bit_rs == 2) 
//            ModeMotor(Backward, 66534, 66534); 
//        else if (bit_rs == 3) 
//            ModeMotor(Left, 20000, 20000); 
//        else if (bit_rs == 4) 
//            ModeMotor(Right, 20000, 20000); 
}

ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &calc_pwm_values);

void setup(void) {
    nh.initNode();
    robot_stop();
    nh.advertise(rightPub);
    nh.advertise(leftPub);
    nh.subscribe(subCmdVel);
}

void loop(void) {
    nh.spinOnce();
    currentMillis = SysTick->VAL;

    if (currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;
        leftPub.publish(&left_wheel_tick_count);
        rightPub.publish(&right_wheel_tick_count);

        calc_vel_right_wheel();
        calc_vel_left_wheel();
    }

    if ((SysTick->VAL / 1000) - lastCmdVelReceived > 1) {
        robot_stop();
    }

    set_pwm_values();
}
