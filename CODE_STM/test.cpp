/***************************************************************************
 * @file    mainpp.cpp
 * @brief   Main program for the AGV (Autonomous Guided Vehicle) project
 * @details This file serves as the core of the AGV system, providing the primary
 *          interface and functionalities required for autonomous navigation and control.
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 *****************************************************************************************************/
#include "mainpp.h"
#include "ros.h"
#include <String.h>
#include "Int16.h"
#include "Float64.h"
#include "Int32.h"
#include "Twist.h"
#include "Encoder.h"
extern "C" {
    #include "BTS7960.h" 
}
extern "C" {
    #include "Encoder.h" 
}

ros::NodeHandle nh;

/* Keep track of the number of wheel ticks */
std_msgs::Int16 right_wheel_tick_count;
//ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);

std_msgs::Int16 left_wheel_tick_count;
//ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

std_msgs::Int16 left_vel_data;
//ros::Publisher leftVelPub("left_wheel_vel", &left_vel_data);

std_msgs::Int16 right_vel_data;
//ros::Publisher rightVelPub("right_wheel_vel", &right_vel_data);

//geometry_msgs::Twist core_data;
//ros::Publisher CoreData("core_info", &core_data);

volatile long pos_left = 0;
volatile long pos_right = 0;

/* direction of motor */
int Direction_left = 1;
int Direction_right = 1;

const int encoder_minimum = -32768;
const int encoder_maximum = 32767;

/* Time interval for measurements in milliseconds */
const int interval = 30;
long previousMillis = 0;
long currentMillis = 0;

/* How much the PWM value can change each cycle */
const int PWM_INCREMENT = 1;

/* Number of ticks per wheel revolution. We won't use this in this code. */
const int TICKS_PER_REVOLUTION = 2688; //620: origin - 800: for left wheel real - 810: for right wheel real

/* Wheel radius in meters */
const double WHEEL_RADIUS = 0.0425;

/* Distance from center of the left tire to the center of the right tire in m */
const double WHEEL_BASE = 0.36;

/* Number of ticks a wheel makes moving a linear distance of 1 meter
 This value was measured manually. */
const double TICKS_PER_METER = 10067; // Originally 2880

/* Proportional constant, which was measured by measuring the
 PWM-Linear Velocity relationship for the robot. */
const int K_P = 278;

/* Y-intercept for the PWM-Linear Velocity relationship for the robot */
const int b = 52;

/* Correction multiplier for drift. Chosen through experimentation. */ 
const int DRIFT_MULTIPLIER = 120;

/*	Turning PWM output (0 = min, 255 = max for PWM values)		*/ 
const int PWM_TURN = 200;

/*	Set maximum and minimum limits for the PWM values			*/ 
const int PWM_MIN = 0; // about 0.1 m/s
const int PWM_MAX = 255; // about 0.172 m/s

/* Set linear velocity and PWM variable values for each wheel	*/ 
double velLeftWheel = 0;
double velRightWheel = 0;
double pwmLeftReq = 0;
double pwmRightReq = 0;

/*	Record the time that the last velocity command was received		*/ 
double vel_left = 0;
double vel_right = 0;
/*  Record the time that the last velocity command was received			*/
double lastCmdVelReceived = 0;

/*	Direction of robot		*/ 
int leftwheel_dir = 0;
int rightwheel_dir = 0;

int is_recv_left_wheel = 0;
int is_recv_right_wheel = 0;
int robot_dir = 0;
long prevT = 0;
float eintegral_r = 0;
float eintegral_l = 0;
int pwmout1 = 0;
int pwmout2 = 0;
int pre_robot_dir = 0;

const int PI = 3.141593;
const int K = 257;

float left_wheel_vel = 0.;
float right_wheel_vel = 0.;
/*	For ROS communicate	*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}


void Encoder_Turnleft(void){
 int b1 = readEncoder1() ;

    	if(b1 == 0){
    		Direction_left = 1;
    	}
    	else if (b1 > 0){
    		Direction_left = 0;
    	}

    	if(Direction_left == 1){
    		if (pos_left == encoder_maximum){
    			pos_left = encoder_minimum;
    		}
    		else{
    			pos_left++;
    		}
    	}
    	else {
    	    if (pos_left == encoder_minimum) {
    	    	pos_left = encoder_maximum;
    	    }
    	    else {
    	    	pos_left--;
    	    }
    	} left_wheel_tick_count.data = pos_left;
 }
void Encoder_Turnright(void){
 	int b2 = readEncoder2();

    	if(b2 == 0){
    		Direction_right = 0;
    	}
    	else if (b2 > 0){
    		Direction_right = 1;
    	}

    	if(Direction_right == 1){
    		if (pos_right == encoder_maximum){
    			pos_right = encoder_minimum;
    		}
    		else{
    			pos_right++;
    		}
    	}
    	else {
    	    if (pos_right == encoder_minimum) {
    	    	pos_right = encoder_maximum;
    	    }
    	    else {
    	    	pos_right--;
    	    }
    	}
    	right_wheel_tick_count.data = pos_right;
    }

/////////////////////// Motor Controller Functions ////////////////////////////

// Calculate the left wheel linear velocity in m/s every time a
// tick count message is rpublished on the /left_ticks topic.
void calc_vel_left_wheel(){

	// Previous timestamp
	static double prevTime = 0;

	// Variable gets created and initialized the first time a function is called.
	static int prevLeftCount = 0;

	// Manage rollover and rollunder when we get outside the 16-bit integer range
	int numOfTicks = (65535 + left_wheel_tick_count.data - prevLeftCount) % 65535;

	// If we have had a big jump, it means the tick count has rolled over.
	if (numOfTicks > 10000) {
		numOfTicks = 0 - (65535 - numOfTicks);
	}

	// Calculate wheel velocity in meters per milisecond
	velLeftWheel = numOfTicks/TICKS_PER_METER/(HAL_GetTick()-prevTime);

	// Calculate right wheel velocity in RPM
	left_wheel_vel = velLeftWheel*30000.0/PI/WHEEL_RADIUS;

	left_vel_data.data = int(left_wheel_vel);
	// Keep track of the previous tick count
	prevLeftCount = left_wheel_tick_count.data;

	// Update the timestamp
	prevTime = HAL_GetTick();

}

// Calculate the right wheel linear velocity in m/s every time a
// tick count message is published on the /right_ticks topic.
void calc_vel_right_wheel(){

	// Previous timestamp
	static double prevTime = 0;

	// Variable gets created and initialized the first time a function is called.
	static int prevRightCount = 0;

	// Manage rollover and rollunder when we get outside the 16-bit integer range
	int numOfTicks = (65535 + right_wheel_tick_count.data - prevRightCount) % 65535;

	if (numOfTicks > 10000) {
		numOfTicks = 0 - (65535 - numOfTicks);
	}

	// Calculate wheel velocity in meters per milisecond
	velRightWheel = numOfTicks/TICKS_PER_METER/(HAL_GetTick()-prevTime);

	// Calculate right wheel velocity in RPM
	right_wheel_vel = velRightWheel*30000.0/PI/WHEEL_RADIUS;
	right_vel_data.data = int(right_wheel_vel);
	prevRightCount = right_wheel_tick_count.data;

	prevTime = HAL_GetTick();

}

void calc_left_wheel_query(const std_msgs::Int16& vel){
    is_recv_left_wheel = 1;
    vel_left = vel.data;
    lastCmdVelReceived = (HAL_GetTick()/1000);
}

void calc_right_wheel_query(const std_msgs::Int16& vel){
    vel_right = vel.data;
    is_recv_right_wheel = 1;
    lastCmdVelReceived = (HAL_GetTick()/1000);
}

int gain_dir(int x, int y){
	if( x > 0 && y > 0){
	  return 1;                                   // ti?n tru?c
	}

	else if(( x > 0 && y < 0) || (x > 0 && y == 0) || (x == 0 && y < 0)){
	  return 2;                                   // quay ph?i
	}

	else if(( x < 0 && y > 0) || (x == 0 && y > 0) || (x < 0 && y == 0)){
	  return 3;                                  // quay trái
	}

	else if(x < 0 && y < 0 ){
	  return 4;                                   // lùi sau
	}

	else{                                         // d?ng yên
	  return 0;
	}
}

void set_pwm_values(int dir, double pwm_left, double pwm_right) {

	// These variables will hold our desired PWM values
	static int pwmLeftOut = 0;
	static int pwmRightOut = 0;

	// Calculate the output PWM value by making slow changes to the current value
	if (abs(pwmLeftReq) > pwmLeftOut) {
		pwmLeftOut += PWM_INCREMENT;
	}
	else if (abs(pwmLeftReq) < pwmLeftOut) {
		pwmLeftOut -= PWM_INCREMENT;
	}
	else{}

	if (abs(pwmRightReq) > pwmRightOut) {
		pwmRightOut += PWM_INCREMENT;
	}
	else if(abs(pwmRightReq) < pwmRightOut) {
		pwmRightOut -= PWM_INCREMENT;
	}
	else{}

	// Conditional operator to limit PWM output at the maximum
	pwmLeftOut = (pwmLeftOut > PWM_MAX) ? PWM_MAX : pwmLeftOut;
	pwmRightOut = (pwmRightOut > PWM_MAX) ? PWM_MAX : pwmRightOut;

	// PWM output cannot be less than 0
	pwmLeftOut = (pwmLeftOut < 0) ? 0 : pwmLeftOut;
	pwmRightOut = (pwmRightOut < 0) ? 0 : pwmRightOut;

	// convert pwm in 16 bit type
	pwmout1 = pwmLeftOut*K;
	pwmout2 = pwmRightOut*K;

	// Set the PWM value on the pins

	switch (dir) {

			    case FORWARD:
			        ModeMotor(FORWARD, pwmout1, pwmout2);
			        break;
			    case TURNRIGHT:
			        ModeMotor(TURNRIGHT, pwmout1, pwmout2);
			        break;
			    case TURNLEFT:
			        ModeMotor(TURNLEFT, pwmout1, pwmout2);
			        break;
			    case BACKWARD:
			        ModeMotor(BACKWARD, pwmout1, pwmout2);
			        break;
			    default:
			    	ModeMotor(STOP, 0, 0);
			        break;
			}
}


// Set up ROS subscriber to the velocity command

ros::Subscriber<std_msgs::Int16> left_wheel_query("left_wheel_query", &calc_left_wheel_query );
ros::Subscriber<std_msgs::Int16> right_wheel_query("right_wheel_query", &calc_right_wheel_query );

void setup(void)
{
  nh.initNode();
  ModeMotor(STOP, 0, 0);
  Dio_Init();
  setupVectorTable() ;
//  nh.advertise(rightPub);
//  nh.advertise(leftPub);
//  nh.advertise(leftVelPub);
//  nh.advertise(rightVelPub);
  // nh.advertise(DirData);
//  nh.advertise(CoreData);
  nh.subscribe(left_wheel_query);
  nh.subscribe(right_wheel_query);

}

void loop(void)
{
//	robot_forward(35000, 35000);
//	HAL_Delay(2000);
//	robot_stop();
//	HAL_Delay(2000);
	nh.spinOnce();

	// Record the time
	currentMillis = HAL_GetTick();

	// If the time interval has passed, publish the number of ticks,
	// and calculate the velocities.
	if (currentMillis - previousMillis > interval) {

		previousMillis = currentMillis;

		// Publish tick counts to topics
//		leftPub.publish( &left_wheel_tick_count );
//		rightPub.publish( &right_wheel_tick_count );

		// Calculate the velocity of the right and left wheels
		calc_vel_right_wheel();
		calc_vel_left_wheel();

//		leftVelPub.publish( &left_vel_data );
//		rightVelPub.publish( &right_vel_data );

	}

	if (is_recv_left_wheel == 1 && is_recv_right_wheel == 1){

		/* Compute velocity with method 1 */ 
		long currT = HAL_GetTick();
		float deltaT = ((float) (currT-prevT))/1000;

		/* -- ROBOT RUN MANUALLY --
		 -- set vel target for left motor -- */
		float vtl = abs(vel_left);
		float kpl = 5;
		float kil = 0;
		float el = vtl - abs(left_wheel_vel);
		eintegral_l = eintegral_l + el*deltaT;

		float ul = kpl*el + kil*eintegral_l;

		pwmLeftReq = fabs(ul);

		if(pwmLeftReq > PWM_MAX){
			pwmLeftReq = PWM_MAX;
		}

		// -- set vel target for right motor --
		float vtr = abs(vel_right);
		float kpr = 5;
		float kir = 0;
		float er = vtr - abs(right_wheel_vel);
		eintegral_r = eintegral_r + er*deltaT;

		float ur = kpr*er + kir*eintegral_r;

		pwmRightReq = fabs(ur);

		if(pwmRightReq > PWM_MAX){
			pwmRightReq = PWM_MAX;
		}

		/* -- robot run --
		 determine direction of robot */
		robot_dir = gain_dir(vel_left, vel_right);

		// Case 1: robot stop => reset variables
		if (robot_dir == 0) {
			ul = 0;
			pwmLeftReq = 0;
			eintegral_l = 0;

			ur = 0;
			pwmRightReq = 0;
			eintegral_r = 0;

		}

		/* Case 2: robot change dir => stop robot before running */
		if (pre_robot_dir != robot_dir){
			pre_robot_dir = robot_dir;
			ul = 0;
			pwmLeftReq = 0;
			eintegral_l = 0;

			ur = 0;
			pwmRightReq = 0;
			eintegral_r = 0;
		}

		/* Stop the car if there are no cmd_vel messages	*/ 
		if((HAL_GetTick()/1000) - lastCmdVelReceived > 1) {
			pwmLeftReq = 0;
			pwmRightReq = 0;
		}

		set_pwm_values(robot_dir, pwmLeftReq, pwmRightReq);

		/* update time */
		prevT = currT;
//		core_data.linear.x = pwmLeftReq;
//		core_data.linear.y = pwmRightReq;
//		core_data.angular.x = pwmout1;
//		core_data.angular.y = pwmout2;
//		core_data.linear.z = robot_dir;
//
//		CoreData.publish(&core_data);

	}
}

