#ifndef ARM_STATE
#define ARM_STATE

#define PROTOCOL_VERSION 1.0
#define DEVICE_NAME "/dev/ttyUSB0"
#define BAUDRATE 9600

class ArmState {
private:
    int m_angle;
    int m_position;
public:
    int getAngle();
    int getPosition();
};

#endif