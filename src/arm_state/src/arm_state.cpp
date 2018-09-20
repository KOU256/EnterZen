/* ヘッダファイルのインクルード */
#include <iostream>
#include <dynamixel_sdk/dynamixel_sdk.h>
#include <ros/ros.h>
#include "arm_state/arm_state.hpp"

/* main関数 */
int main(int argc, char **argv) {
    ArmState arm_state[3];                                              //ArmStateクラスのインスタンス

    dynamixel::PortHandler * port_handler =
        dynamixel::PortHandler::getPortHandler(DEVICE_NAME);            //PortHandllerクラスのインスタンス
    dynamixel::PacketHandler * packet_handler =
        dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);   //PacketHandlerクラスのインスタンス

    /* USBデバイスのポートを開く*/
    if (port_handler->openPort()) {
        std::cout << "openPort Succeeded" << std::endl;
    }
    else {
        std::cout << "openPort Failed" << std::endl;
    }

    /* ボーレートをセット */
    if (port_handler->setBaudRate(BAUD_RATE)) {
        std::cout << "setBaudRate Succeeded" << std::endl;
    }
    else {
        std::cout << "setBaudRate Failed" << std::endl;
    }

    /* 各Dynamixelの位置と角度を取得して出力 */
    for (int i = FIRST_DXL_ID; i <= THIRD_DXL_ID; i++){
        std::cout
        << "ID:" << i << " "
        << arm_state[i].getPosition(i, port_handler, packet_handler) << " "
        << arm_state[i].getAngle() << std::endl;
    }

    return 0;
}

/* Dynamixelの位置を返す関数 */
int ArmState::getPosition(int id, dynamixel::PortHandler * port, dynamixel::PacketHandler * packet) {
    int result;         //通信の結果
    uint8_t error = 0;  //通信で発生したエラー

    /* 指定したIDにパケットを送信 */
    result = packet->read2ByteTxRx(port, id, PRESENT_POSITION_ADDR, &m_position, &error);

    /* 位置を取得できれば位置を返し、エラーが発生すればエラーメッセージを表示して-1を返す */
    if (result == COMM_SUCCESS) {
        return (int)m_position;
    }
    else {
        std::cout
        << packet->getTxRxResult(result) << std::endl
        << packet->getRxPacketError(error) << std::endl;
        return -1;
    }
}

/* Dynamixelの角度を返す関数 */
int ArmState::getAngle() {
    float step; //分解能

    /* 位置を角度に変換 */
    step = (float)ANGLE_RANGE / (float)POSITION_RANGE;
    m_angle = step * m_position;

    return m_angle;
}