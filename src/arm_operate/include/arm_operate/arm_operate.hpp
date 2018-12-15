#ifndef ARM_OPERATE
#define ARM_OPERATE

#define PROTOCOL_VERSION 1.0                //Dynamixelのプロトコルのバージョン
#define DEVICE_NAME "/dev/ttyUSB0"          //USBデバイス名
#define BAUD_RATE 9600                      //Dynamixelのボーレート
#define GOAL_POSITION_ADDR 30               //Goal Positionのアドレス
#define PRESENT_POSITION_ADDR 36            //Present Positionのアドレス

#define DXL_FIRST_ID 0
#define DXL_SECOND_ID 1
#define DXL_THIRD_ID 2
#define DXL_FOURTH_ID 3
#define DXL_NUM 4

class ArmOperate {
private:
public:
    int setGoalPosition(
        int id,
        int goal_position,
        dynamixel::PortHandler * port,
        dynamixel::PacketHandler * packet
    );
};

#endif