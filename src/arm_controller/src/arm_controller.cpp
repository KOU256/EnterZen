
#include <iostream>
#include <unistd.h>

#include "ros/ros.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include "sensor_msgs/Joy.h"
#include "sensor_msgs/JointState.h"

#define ADDR_MX_TORQUE_ENABLE 24
#define ADDR_MX_GOAL_POSITION 30
#define ADDR_MX_PRESENT_POSITION 36

#define PROTOCOL_VERSION 1.0
#define DEVICE_NAME "/dev/ttyUSB0"
#define BAUDRATE 9600

#define DXL_FIRST_ID 0
#define DXL_SECOND_ID 1
#define DXL_THIRD_ID 2
#define DXL_FOURTH_ID 3
#define DXL_NUM 4
#define DXL_MIN_VALUE 0
#define DXL_MAX_VALUE 1023

#define JOY_BORDER 0.7

using namespace std;

int result;
int target_first = 205;
int target_second = 500;
int target_third = 820;
int target_fourth = 512;
int robot_state = 0;  // 0:home 1:pipe_in 2:pipe_out 3:return
int min_angle[DXL_NUM] = {210, 208, 0, 100};
int max_angle[DXL_NUM] = {822, 500, 820, 840};

uint8_t error;
dynamixel::PortHandler *port_handler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
dynamixel::PacketHandler *packet_handler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

void changeDxlAngle(int id, int target_angle) {
    if (target_angle < min_angle[id])
        target_angle = min_angle[id];
    else if (target_angle > max_angle[id])
        target_angle = max_angle[id];

    result = packet_handler->write2ByteTxRx(port_handler, id, ADDR_MX_GOAL_POSITION, target_angle, &error);
}

int moveCameraToHome() {
    changeDxlAngle(DXL_THIRD_ID, 512);
    changeDxlAngle(DXL_FOURTH_ID, 512);
    usleep(500000);
    changeDxlAngle(DXL_SECOND_ID, 208);
    usleep(500000);
    changeDxlAngle(DXL_FIRST_ID, 210);
    usleep(500000);
    changeDxlAngle(DXL_SECOND_ID, 500);
    changeDxlAngle(DXL_THIRD_ID, 820);
    return 0;
}

int moveCameraToPipeIn() {
    changeDxlAngle(DXL_THIRD_ID, 750);
    changeDxlAngle(DXL_FOURTH_ID, 450);
    return 1;
}

int moveCameraToPipeOut() {
    changeDxlAngle(DXL_SECOND_ID, 300);
    changeDxlAngle(DXL_THIRD_ID, 512);
    changeDxlAngle(DXL_FOURTH_ID, 512);
    usleep(500000);
    changeDxlAngle(DXL_FIRST_ID, 822);
    usleep(500000);
    changeDxlAngle(DXL_THIRD_ID, 45);
    return 2;
}

int moveCameraToReturn() {
    changeDxlAngle(DXL_SECOND_ID, 450);
    changeDxlAngle(DXL_THIRD_ID, 720);
    changeDxlAngle(DXL_FOURTH_ID, 450);
    return 3;
}

void joyCallback(const sensor_msgs::Joy::ConstPtr joy)
{
    if (joy->buttons[8]) {
        robot_state = moveCameraToHome();
    }
    else if (joy->buttons[7]) {
        if (robot_state == 0) {
            robot_state = moveCameraToPipeIn();
        }
        if (robot_state == 2) {
            robot_state = moveCameraToReturn();
        }
    }
    else if (joy->buttons[6]) {
        if (robot_state == 1) {
            robot_state = moveCameraToPipeOut();
        }
    }
    else if (joy->buttons[5]) {
        if (joy->axes[4] >= JOY_BORDER) {
            if (robot_state == 2) {
                target_fourth -= 16;
                changeDxlAngle(DXL_FOURTH_ID, target_fourth);
            }
            else if (robot_state == 1 || robot_state == 3) {
                target_fourth += 16;
                changeDxlAngle(DXL_FOURTH_ID, target_fourth);
            }
        }
        if (joy->axes[4] <= -JOY_BORDER) {
            if (robot_state == 2) {
                target_fourth += 16;
                changeDxlAngle(DXL_FOURTH_ID, target_fourth);
            }
            else if (robot_state == 1 || robot_state == 3) {
                target_fourth -= 16;
                changeDxlAngle(DXL_FOURTH_ID, target_fourth);
            }
        }
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