#include <iostream>
#include <dynamixel_sdk/dynamixel_sdk.h>
#include <ros/ros.h>
#include "arm_state/arm_state.hpp"

int main(int argc, char **argv) {
    ArmState arm_state[3];

    dynamixel::PortHandler * port_handler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
    dynamixel::PacketHandler * packet_handler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    
    if (port_handler->openPort()) {std::cout << "openPort Succeeded" << std::endl;}
    else {std::cout << "openPort Failed" << std::endl;}

    if (port_handler->setBaudRate(BAUD_RATE)) {std::cout << "setBaudRate Succeeded" << std::endl;}
    else {std::cout << "setBaudRate Failed" << std::endl;}

    for (int i = FIRST_DXL_ID; i <= THIRD_DXL_ID; i++){
        std::cout << "ID:" << i << " " << arm_state[i].getPosition(i, port_handler, packet_handler) << std::endl;
        std::cout << "ID:" << i << " " << arm_state[i].getAngle() << std::endl;
    }
    return 0;
}

int ArmState::getAngle() {
    float step;

    step = (float)ANGLE_RANGE / (float)POSITION_RANGE;
    m_angle = step * m_position;
    
    return m_angle;
}

int ArmState::getPosition(int id, dynamixel::PortHandler * port, dynamixel::PacketHandler * packet) {
    int result;
    uint8_t error;

    result = packet->read2ByteTxRx(port, id, PRESENT_POSITION_ADDR, &m_position, &error);
    if (result == COMM_SUCCESS) {return (int)m_position;}
    else {return 0;}
}