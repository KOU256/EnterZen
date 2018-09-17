
#include <iostream>

#include "ros/ros.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include "sensor_msgs/Joy.h"
#include "sensor_msgs/JointState.h"

#define FIRST_JOINT_INDEX 0
#define SECOND_JOINT_INDEX 1
#define THIRD_JOINT_INDEX 2

#define ADDR_MX_TORQUE_ENABLE 24
#define ADDR_MX_GOAL_POSITION 30
#define ADDR_MX_PRESENT_POSITION 36

#define PROTOCOL_VERSION 1.0
#define DEVICE_NAME "/dev/ttyUSB0"
#define BAUDRATE 9600

#define DXL_FIRST 1
#define DXL_SECOND 2
#define DXL_THIRD 3
#define DXL_MINIMUM_POTISION_VALUE 0
#define DCL_MAXIMUM_POSITION_VALUE 1023

using namespace std;

float axes[8];
int buttons[11];
int result;
int target_first = 45;
int target_second = 512;
int target_third = 45;

uint8_t error;
dynamixel::PortHandler *port_handler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
dynamixel::PacketHandler *packet_handler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

void joyCallback(const sensor_msgs::Joy::ConstPtr joy) {
	static double first_joint_position = 0;    // first_jointの位置
	static double second_joint_position = 0;    // second_jointの位置
	static double third_joint_position = 0;    // third_jointの位置

	ros::NodeHandle nh;    // NodeHandleクラスのインスタンス
    ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 1000);    // joint_statesへのPublisher

    ros::Rate loop_rate(10);
    while (ros::ok()) {
        sensor_msgs::JointState js;    // JointStateクラスのインスタンス

        js.header.stamp = ros::Time::now();

		// URDFで作成したモデルのjointの数に合わせる
        js.name.resize(3);
        js.position.resize(3);

		// URDFで作成したモデルに合わせた名前をつける
        js.name[FIRST_JOINT_INDEX] = "first_joint";
        js.name[SECOND_JOINT_INDEX] = "second_joint";
        js.name[THIRD_JOINT_INDEX] = "third_joint";

		// 右スティックの横軸に合わせてfirst_jointを回転
        if (joy->axes[3] >= 0.5) {
			first_joint_position += 0.1;
			if (first_joint_position > 1.57) {first_joint_position = 1.57;}

			target_first += 20;
			if (target_first > 971) {target_first = 971;} 
		}
        else if(joy->axes[3] <= -0.5) {
			first_joint_position -= 0.1;
			if (first_joint_position < -3.14) {first_joint_position = -3.14;}

			target_first -= 20;
			if (target_first < 45) {target_first = 45;}
		}

		// Rボタンが押されていないとき、右スティックの縦軸に合わせてsecond_jointを回転
        if (joy->axes[4] >= 0.5 && joy->buttons[5] == 0) {
			second_joint_position -= 0.1;
			if (second_joint_position < -1.57) {second_joint_position = -1.57;}

			target_second += 20;
			if (target_second > 820) {target_second = 820;} 
		}
        else if(joy->axes[4] <= -0.5 && joy->buttons[5] == 0) {
			second_joint_position += 0.1;
			if (second_joint_position > 1.57) {second_joint_position = 1.57;}

			target_second -= 20;
			if (target_second < 205) {target_second = 205;} 
		}

		// Rボタンが押されているとき、右スティックの縦軸に合わせてthird_jointを回転
        if (joy->axes[7] >= 1.0 && joy->buttons[5] == 1) {
			third_joint_position += 0.1;
			if (third_joint_position > 0) {third_joint_position = 0;}

			target_third += 20;
			if (target_second > 971) {target_second = 971;}
		}
        else if(joy->axes[7] <= -1.0 && joy->buttons[5] == 1) {
			third_joint_position -= 0.1;
			if (third_joint_position < -5.71) {third_joint_position = 5.71;}

			target_third -= 20;
			if (target_second < 45) {target_second = 45;}
		}

		// 各jointのpositonを代入
		js.position[FIRST_JOINT_INDEX] = first_joint_position;
		js.position[SECOND_JOINT_INDEX] = second_joint_position;
		js.position[THIRD_JOINT_INDEX] = third_joint_position;
        
		// PublisherでPublishする
        joint_pub.publish(js);
		std::cout << first_joint_position << ',' << second_joint_position << ',' << third_joint_position << std::endl;
		result = packet_handler->write2ByteTxRx(port_handler,DXL_FIRST, ADDR_MX_GOAL_POSITION, target_first, &error);
		result = packet_handler->write2ByteTxRx(port_handler,DXL_SECOND, ADDR_MX_GOAL_POSITION, target_second, &error);
		result = packet_handler->write2ByteTxRx(port_handler,DXL_THIRD, ADDR_MX_GOAL_POSITION, target_third, &error);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char **argv){
	port_handler->openPort();
	port_handler->setBaudRate(BAUDRATE);

    ros::init(argc, argv, "arm_controller");
    ros::NodeHandle n;
	ros::Subscriber joy_input = n.subscribe<sensor_msgs::Joy>("joy", 10, &joyCallback);
	
    ros::spin();

    return 0;
}