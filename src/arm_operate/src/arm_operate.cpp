#include<iostream>
#include <dynamixel_sdk/dynamixel_sdk.h>
#include <ros/ros.h>
#include "arm_operate/arm_operate.hpp"

int main(int argc, char ** argv) {
    dynamixel::PortHandler * port_handler =
        dynamixel::PortHandler::getPortHandler(DEVICE_NAME);            //PortHandllerクラスのインスタンス
    dynamixel::PacketHandler * packet_handler =
        dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);   //PacketHandlerクラスのインスタンス
    int id, goal_position;
    ArmOperate arm_operate;
    port_handler->openPort();
	port_handler->setBaudRate(BAUD_RATE);

    std::cout << "id? : ";
    std::cin >> id;

    std::cout << "position? :";
    std::cin >> goal_position;
    arm_operate.setGoalPosition(id, goal_position, port_handler, packet_handler);

    return 0;
}

int ArmOperate::setGoalPosition(
    int id,
    int goal_position,
    dynamixel::PortHandler *port,
    dynamixel::PacketHandler *packet
) {
    int result;
    uint8_t error;

    result = packet->write2ByteTxRx(port, id, GOAL_POSITION_ADDR, goal_position, &error);

    return result;
};