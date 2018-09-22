#ifndef ARM_OPERATE
#define ARM_OPERATE

#define PROTOCOL_VERSION 1.0                //Dynamixelのプロトコルのバージョン
#define DEVICE_NAME "/dev/ttyUSB0"          //USBデバイス名
#define BAUD_RATE 9600                      //Dynamixelのボーレート
#define GOAL_POSITION_ADDR 30               //Goal Positionのアドレス
#define PRESENT_POSITION_ADDR 36            //Present Positionのアドレス

#define FIRST_DXL_ID 0                      //First Jointで使用しているDynamixelのID
#define SECOND_DXL_ID 1                     //Second Jointで使用しているDynamixelのID
#define THIRD_DXL_ID 2                      //Third Jointで使用しているDynamixelのID
#define DYNAMIXEL_NUM 3

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