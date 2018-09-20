#ifndef ARM_STATE
#define ARM_STATE

#define PROTOCOL_VERSION 1.0
#define DEVICE_NAME "/dev/ttyUSB0"
#define BAUD_RATE 9600
#define GOAL_POSITION_ADDR 30
#define PRESENT_POSITION_ADDR 36

#define FIRST_DXL_ID 0
#define SECOND_DXL_ID 1
#define THIRD_DXL_ID 2

#define POSITION_RANGE 1024
#define ANGLE_RANGE 300

class ArmState {
private:
    int m_angle;
    uint16_t m_position;
public:
    int getAngle();
    int getPosition(int id, dynamixel::PortHandler * port, dynamixel::PacketHandler * packet);
};

#endif