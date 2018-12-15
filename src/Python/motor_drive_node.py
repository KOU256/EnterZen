#!/usr/bin/env python

import rospy
import pigpio
import time
from std_msgs.msg import Int32MultiArray, Int32
from sensor_msgs.msg import Joy

# constant
JOY_BORDER = 0.7          # joy stick border = +-0.7
ANGLE_LIMIT = 90          # max angle = +-60degree

REAR =  0                 # pin_pwm:   10, pin_a:   9, pin_b:   11
FRONT = 1                 # pin_pwm:   13, pin_a:  16, pin_b:   19
LIFT =  2                 # pin_pwm:   5, pin_a:  12, pin_b:  6
LEFT =  3                 # pin_pwm:   15, pin_a:  18, pin_b:  22
RIGHT = 4                 # pin_pwm:   20, pin_a:  26, pin_b:   21

# [REAR(C), FRONT(D), LIFT(E), LEFT(A), RIGHT(B)]

PWM =      [10, 13,  5, 15, 20]
OUTPUT_A = [ 9, 16, 12, 18, 26]
OUTPUT_B = [11, 19,  6, 22, 21]

# global variable
# [REAR(C), FRONT(D), LIFT(E)]
#curr_angle = [0, 0]    # current angle
rear_angle = 0
front_angle = 0
lift_angle = 0

# instance
pi = pigpio.pi()          # pigpio class

def init_output_pin(motor_name):
    """
    initialize output pins "mode", "dutycycle", "frequency", "pin level"
    """

    pi.set_mode(PWM[motor_name], pigpio.OUTPUT)
    pi.set_mode(OUTPUT_A[motor_name], pigpio.OUTPUT)
    pi.set_mode(OUTPUT_B[motor_name], pigpio.OUTPUT)

    pi.set_PWM_dutycycle(PWM[motor_name], 0)
    pi.set_PWM_frequency(PWM[motor_name], 1000)

    pi.write(PWM[motor_name], 0)
    pi.write(OUTPUT_A[motor_name], 0)
    pi.write(OUTPUT_B[motor_name], 0)

def change_dutycycle(motor_name, dutycycle):
    """
    dutycycle 0-255
    """

    if dutycycle > 255:
        dutycycle = 255
    elif dutycycle < 0:
        dutycycle = 0

    pi.set_PWM_dutycycle(PWM[motor_name], dutycycle)

def drive_motor(motor_name, rotation, dutycycle):
    """
    Drive Motor "cw", "ccw", "brake and stop"
    """

    change_dutycycle(motor_name, dutycycle)

    if rotation == 1:    # cw
        pi.write(OUTPUT_A[motor_name], 1)
        pi.write(OUTPUT_B[motor_name], 0)
        pi.write(PWM[motor_name], 1)
    elif rotation == -1: # ccw
        pi.write(OUTPUT_A[motor_name], 0)
        pi.write(OUTPUT_B[motor_name], 1)
        pi.write(PWM[motor_name], 1)
    elif rotation == 0:  # brake and stop
        pi.write(OUTPUT_A[motor_name], 1)
        pi.write(OUTPUT_B[motor_name], 1)

        pi.write(OUTPUT_A[motor_name], 0)
        pi.write(OUTPUT_B[motor_name], 0)
        pi.write(PWM[motor_name], 0)

def move_machine(direction, dutycycle):
    """
    Move Machine "go", "back
    """

    if direction == "go":
        drive_motor(LEFT, -1, dutycycle)
        drive_motor(RIGHT, 1, dutycycle)
    elif direction == "back":
        drive_motor(LEFT, 1, dutycycle)
        drive_motor(RIGHT, -1, dutycycle)

def turn_machine(direction, dutycycle):
    """
    Turn Machine "left", "right"
    """

    if direction == "left":
        drive_motor(LEFT, 1, dutycycle)
        drive_motor(RIGHT, 1, dutycycle)
    elif direction == "right":
        drive_motor(LEFT, -1, dutycycle)
        drive_motor(RIGHT, -1, dutycycle)

def stop_machine():
    """
    Stop Machine "Move", "Turn"
    """

    drive_motor(LEFT, 0, 0)
    drive_motor(RIGHT, 0, 0)

def elevating_lift(direction, dutycycle):
    """
    Elevate Lift "up", "down", "stop"
    """

    if direction == "up":
        drive_motor(LIFT, 1, dutycycle)
    elif direction == "down":
        drive_motor(LIFT, -1, dutycycle)
    elif direction == "stop":
        drive_motor(LIFT, 0, dutycycle)

def joy_callback(msg):
    print rear_angle, front_angle, lift_angle
    if msg.axes[0] <= -JOY_BORDER:
        turn_machine("right", -msg.axes[0] * 128)
    elif msg.axes[0] >= JOY_BORDER:
        turn_machine("left", msg.axes[0] * 128)
    elif msg.axes[1] <= -JOY_BORDER:
        move_machine("back", -msg.axes[1] * 128)
    elif msg.axes[1] >= JOY_BORDER:
        move_machine("go", msg.axes[1] * 128)
    elif abs(msg.axes[0]) < JOY_BORDER and abs(msg.axes[1]) < JOY_BORDER:
        stop_machine()
    if msg.buttons[0] == 1:
        if msg.axes[4] >= JOY_BORDER and rear_angle < ANGLE_LIMIT:
            drive_motor(REAR, -1, 64)
        elif msg.axes[4] <= -JOY_BORDER and rear_angle > -ANGLE_LIMIT:
            drive_motor(REAR, 1, 64)
    elif msg.buttons[1] == 1:
        if msg.axes[4] >= JOY_BORDER and front_angle < ANGLE_LIMIT:
            drive_motor(FRONT, -1, 64)
        elif msg.axes[4] <= -JOY_BORDER and front_angle > -ANGLE_LIMIT:
            drive_motor(FRONT, 1, 64)
    else:
        if msg.axes[4] >= JOY_BORDER and rear_angle < ANGLE_LIMIT:
            drive_motor(REAR, -1, 64)
            drive_motor(FRONT, -1, 64)
        elif msg.axes[4] <= -JOY_BORDER and rear_angle > -ANGLE_LIMIT:
            drive_motor(REAR, 1, 64)
            drive_motor(FRONT, 1, 64)
        elif abs(msg.axes[4]) < JOY_BORDER and msg.buttons[0] + msg.buttons[1] + msg.buttons[2] + msg.buttons[3] == 0 :
            drive_motor(REAR, 0, 0)
            drive_motor(FRONT, 0, 0)

    #elif msg.buttons[0] == 1 and rear_angle < ANGLE_LIMIT:
    #    drive_motor(REAR, -1, 100)
    #elif msg.buttons[1] == 1 and rear_angle > -ANGLE_LIMIT:
    #    drive_motor(REAR, 1, 100)
    #elif msg.buttons[2] == 1 and front_angle < ANGLE_LIMIT:
    #    drive_motor(FRONT, -1, 100)
    #elif msg.buttons[3] == 1 and front_angle > -ANGLE_LIMIT:
    #    drive_motor(FRONT, 1, 100)

    if msg.axes[7] == -1.0:
        elevating_lift("down", 255)
    elif msg.axes[7] == 1.0:
        elevating_lift("up", 255)
    elif msg.axes[7] == 0:
        elevating_lift("stop", 0)

#def sensor_callback(msg):
#    global curr_angle
#    curr_angle = msg.data
#    #print curr_angle[0]

def rear_callback(msg):
    global rear_angle
    rear_angle = msg.data

def front_callback(msg):
    global front_angle
    front_angle = msg.data

def lift_callback(msg):
    global lift_angle
    lift_angle = msg.data
    #print 'lift_angle = %d' % lift_angle

def subscriber():
    rospy.init_node("motor_drive_node")
    rospy.Subscriber("joy", Joy, joy_callback)
    #rospy.Subscriber("sensor", Int32MultiArray, sensor_callback)
    rospy.Subscriber("rear", Int32, rear_callback)
    rospy.Subscriber("front", Int32, front_callback)
    rospy.Subscriber("lift", Int32, lift_callback)
    rospy.spin()

if __name__ == '__main__':
    motor = [REAR, FRONT, LIFT, LEFT, RIGHT]
    for m in motor:
        init_output_pin(m)

    subscriber()
