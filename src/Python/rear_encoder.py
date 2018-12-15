#!/usr/bin/env python
import rospy
import pigpio
import time
from std_msgs.msg import Int32

# [14, 4], [2, 3], [17, 27]
INPUT_A = 14
INPUT_B = 4

curr_count = 0
prev_count = 0
is_rotary = 0
prev_a_phase = 0
curr_a_phase = 0

pi = pigpio.pi()
rospy.init_node('rear_encoder_node', anonymous=True)
pub = rospy.Publisher('rear', Int32, queue_size=100)
pub_rate = rospy.Rate(10)
msg = Int32()

def encoder_data_publisher():
    global curr_count
    msg.data = 360 / 400 * curr_count
    pub.publish(msg)
    print "REAR ANGLE : %d" % (360 / 400 * curr_count)

def init_input_pin(in_a, in_b):
    pi.set_mode(in_a, pigpio.INPUT)
    pi.set_pull_up_down(in_a, pigpio.PUD_UP)
    pi.set_mode(in_b, pigpio.INPUT)
    pi.set_pull_up_down(in_b, pigpio.PUD_UP)

def count_rotary():
    global curr_count
    global is_rotary
    global prev_a_phase
    global curr_a_phase
    prev_a_phase = pi.read(INPUT_A)
    while (not pi.read(INPUT_B)):
        curr_a_phase = pi.read(INPUT_A)
        is_rotary = 1
    if is_rotary == 1:
        is_rotary = 0
        if (prev_a_phase == 0) and (curr_a_phase == 1):
            curr_count += 1
        if (prev_a_phase == 1) and (curr_a_phase == 0):
            curr_count -= 1

def loop():
    global curr_count
    global prev_count
    while True:
        prev_count = curr_count
        count_rotary()
        if (prev_count != curr_count):
            encoder_data_publisher()
            #print 'global_counter = %d' % curr_count

def destroy():
    pi.stop()

if __name__ == '__main__':
    init_input_pin(INPUT_A, INPUT_B)
    try:
        loop()
    except rospy.ROSInterruptException:
        destroy()