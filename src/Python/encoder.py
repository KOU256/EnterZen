#!/usr/bin/env python
import rospy
import pigpio
from std_msgs.msg import Int32MultiArray

REAR  = 0    #pin_a: 14, pin_b:  4
FRONT = 1    #pin_a:  2, pin_b:  3
# LIFT  = 2    #pin_a: 17, pin_b: 27

# [REAR(C), FRONT(D), LIFT(E)]
# INPUT_A = [14, 2, 17]
# INPUT_B = [4,  3, 27]
INPUT_A = [14, 2]
INPUT_B = [4, 3]


MAX_ANGLE = 360.0
MAX_COUNT = 200.0

# curr_count =   [0, 0, 0]
# prev_count =   [0, 0, 0]
# is_rotary =    [0, 0, 0]
# prev_a_phase = [0, 0, 0]
# curr_a_phase = [0, 0, 0]
curr_count =   [0, 0]
prev_count =   [0, 0]
is_rotary =    [0, 0]
prev_a_phase = [0, 0]
curr_a_phase = [0, 0]


pi = pigpio.pi()
rospy.init_node("encoder_node")
pub = rospy.Publisher("sensor", Int32MultiArray, queue_size=100)
pub_rate = rospy.Rate(10)
msg = Int32MultiArray()
#msg.data = [0, 0, 0]
msg.data = [0, 0]

def encoder_data_publisher():
    msg.data[REAR] = convert_count_to_angle(curr_count[REAR])
    msg.data[FRONT] = convert_count_to_angle(curr_count[FRONT])
    #msg.data[LIFT] = convert_count_to_angle(curr_count[LIFT])
    pub.publish(msg)

def convert_count_to_angle(count):
    return MAX_ANGLE / MAX_COUNT * count

def init_input_pin(motor_name):
    pi.set_mode(INPUT_A[motor_name], pigpio.INPUT)
    pi.set_mode(INPUT_B[motor_name], pigpio.INPUT)

    pi.set_pull_up_down(INPUT_A[motor_name], pigpio.PUD_UP)
    pi.set_pull_up_down(INPUT_B[motor_name], pigpio.PUD_UP)

def count_rotary(motor_name):
    global curr_count
    global is_rotary
    global prev_a_phase
    global curr_a_phase
    prev_a_phase[motor_name] = pi.read(INPUT_A[motor_name])
    while (not pi.read(INPUT_B[motor_name])):
        curr_a_phase[motor_name] = pi.read(INPUT_A[motor_name])
        is_rotary[motor_name] = 1
    if is_rotary[motor_name] == 1:
        is_rotary[motor_name] = 0
        if (prev_a_phase[motor_name] == 0) and (curr_a_phase[motor_name] == 1):
            curr_count[motor_name] += 1
        if (prev_a_phase[motor_name] == 1) and (curr_a_phase[motor_name] == 0):
            curr_count[motor_name] -= 1

#def timer_callback(event):


def loop():
    global curr_count
    #motor = [REAR, FRONT, LIFT]
    motor = [REAR, FRONT]
    while not rospy.is_shutdown():
        for m in motor:
            prev_count[m] = curr_count[m]
            count_rotary(m)
        #if (prev_count[m] != curr_count[m]):
        print curr_count[REAR], curr_count[FRONT]
        encoder_data_publisher()

def destroy():
    pi.stop()

if __name__ == '__main__':
    #motor = [REAR, FRONT, LIFT]
    motor = [REAR, FRONT]
    for m in motor:
        init_input_pin(m)
    try:
        loop()
    except KeyboardInterrupt or rospy.ROSInterruptException :
        destroy()