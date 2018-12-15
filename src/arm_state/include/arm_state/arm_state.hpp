#ifndef ARM_STATE
#define ARM_STATE

#define TOPIC_QUEUE_SIZE 100                //トピックキューのサイズ
#define LOOP_RATE 1                         //パブリッシャーのループ時間

#define PROTOCOL_VERSION 1.0                //Dynamixelのプロトコルのバージョン
#define DEVICE_NAME "/dev/ttyUSB0"          //USBデバイス名
#define BAUD_RATE 9600                      //Dynamixelのボーレート
#define GOAL_POSITION_ADDR 30               //Goal Positionのアドレス
#define PRESENT_POSITION_ADDR 36            //Present Positionのアドレス

#define DXL_FIRST_ID 0                      //First Jointで使用しているDynamixelのID
#define DXL_SECOND_ID 1                     //Second Jointで使用しているDynamixelのID
#define DXL_THIRD_ID 2                      //Third Jointで使用しているDynamixelのID
#define DXL_FOURTH_ID 3                     //Fourth Jointで使用しているDynamixelのID
#define DXL_NUM 4

#define POSITION_RANGE 1024                 //Dynamixelの稼働範囲(位置)
#define ANGLE_RANGE 300                     //Dynamixelの可動範囲(角度)

class ArmState {
private:
    uint16_t m_position;                    //Dynamixelの位置
    int m_angle;                            //Dynamixelの角度
public:
    int getPosition(
        int id,
        dynamixel::PortHandler * port,
        dynamixel::PacketHandler * packet
    );                                      //Dynamixelの位置を返す関数
    int getAngle();                         //Dynamixelの角度を返す関数
};

#endif