#!/usr/bin/env python

import rospy
import pigpio
import time
from std_msgs.msg import Int32MultiArray
from sensor_msgs.msg import Joy

# constant
JOY_BORDER = 0.7          # joy stick border = +-0.7
ANGLE_LIMIT = 30          # max angle = +-60degree
KP = 2.0                  # propotinal gain = 1.0

REAR =  0                 # pin_a:   5, pin_b:   7
FRONT = 1                 # pin_a:  13, pin_b:   6
LIFT =  2                 # pin_a:  26, pin_b:  19
LEFT =  3                 # pin_a:  10, pin_b:  22
RIGHT = 4                 # pin_a:  11, pin_b:   9

# [REAR(C), FRONT(D), LIFT(E), LEFT(A), RIGHT(B)]
OUTPUT_A = [5, 13, 26, 10, 11]
OUTPUT_B = [7,  6, 19, 22,  9]

# variable
# [REAR(C), FRONT(D), LIFT(E)]
curr_angle = [0]    # current angle
target_angle = [0, 0]  # target angle

# instance
pi = pigpio.pi()          # pigpio class

def init_output_pin(motor_name):
    """
    initialize output pins "mode", "dutycycle", "frequency", "pin level"
    """

    pi.set_mode(OUTPUT_A[motor_name], pigpio.OUTPUT)
    pi.set_mode(OUTPUT_B[motor_name], pigpio.OUTPUT)

    pi.set_PWM_dutycycle(OUTPUT_A[motor_name], 0)
    pi.set_PWM_dutycycle(OUTPUT_B[motor_name], 0)

    pi.set_PWM_frequency(OUTPUT_A[motor_name], 1000)
    pi.set_PWM_frequency(OUTPUT_B[motor_name], 1000)

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

    pi.set_PWM_dutycycle(OUTPUT_A[motor_name], dutycycle)
    pi.set_PWM_dutycycle(OUTPUT_B[motor_name], dutycycle)

def drive_motor(motor_name, rotation, dutycycle):
    """
    Drive Motor "cw", "ccw", "brake and stop"
    """

    change_dutycycle(motor_name, dutycycle)

    if rotation == 1:    # cw
        pi.write(OUTPUT_A[motor_name], 1)
        pi.write(OUTPUT_B[motor_name], 0)
    elif rotation == -1: # ccw
        pi.write(OUTPUT_A[motor_name], 0)
        pi.write(OUTPUT_B[motor_name], 1)
    elif rotation == 0:  # brake and stop
        pi.write(OUTPUT_A[motor_name], 1)
        pi.write(OUTPUT_B[motor_name], 1)

        pi.write(OUTPUT_A[motor_name], 0)
        pi.write(OUTPUT_B[motor_name], 0)

def move_machine(direction, dutycycle):
    """
    Move Machine "go", "back
    """

    if direction == "go":
        drive_motor(LEFT, 1, dutycycle)
        drive_motor(RIGHT, -1, dutycycle)
    elif direction == "back":
        drive_motor(LEFT, -1, dutycycle)
        drive_motor(RIGHT, 1, dutycycle)

def turn_machine(direction, dutycycle):
    """
    Turn Machine "left", "right"
    """

    if direction == "left":
        drive_motor(LEFT, -1, dutycycle)
        drive_motor(RIGHT, -1, dutycycle)
    elif direction == "right":
        drive_motor(LEFT, 1, dutycycle)
        drive_motor(RIGHT, 1, dutycycle)

def stop_machine():
    """
    Stop Machine "Move", "Turn"
    """

    drive_motor(LEFT, 0, 0)
    drive_motor(RIGHT, 0, 0)

def change_crawler_angle(rotation):
    """
    Crawler Angle "up", "down", "reset"
    """

    global target_angle
    if not abs(curr_angle[REAR]) > ANGLE_LIMIT:
        if rotation == "up":
            target_angle[REAR] += 10
            target_angle[FRONT] += 10
            if target_angle[REAR] > ANGLE_LIMIT:
                target_angle[REAR] = target_angle[FRONT] = ANGLE_LIMIT
            drive_motor(REAR, -1, KP * abs(target_angle[REAR] - curr_angle[REAR]))
            #drive_motor(FRONT, -1, KP * abs(target_angle[FRONT] - curr_angle[REAR]))       # because FRONT encoder is malfunction
        elif rotation == "down":
            target_angle[REAR] -= 10
            target_angle[FRONT] -= 10
            if target_angle[REAR] < -ANGLE_LIMIT:
                target_angle[REAR] = target_angle[FRONT] = -ANGLE_LIMIT

            drive_motor(REAR, 1, KP * abs(target_angle[REAR] - curr_angle[REAR]))
            #drive_motor(FRONT, 1, KP * abs(target_angle[FRONT] - curr_angle[REAR]))        # because FRONT encoder is malfunction

        elif rotation == "reset":
            target_angle[REAR] = 0
            target_angle[FRONT] = 0

          # if curr_angle[REAR] > 0 and curr_angle[FRONT] > 0:
            if curr_angle[REAR] > 0:                                                    # because FRONT encoder is malfunction
                drive_motor(REAR, 1, KP * abs(target_angle[REAR] - curr_angle[REAR]))
                #drive_motor(FRONT, 1, KP * abs(target_angle[FRONT] - curr_angle[REAR]))    # because FRONT encoder is malfunction
          # elif curr_angle[REAR] < 0 and curr_angle[FRONT] < 0:
            elif curr_angle[REAR] < 0:                                                  # because FRONT encoder is malfunction
                drive_motor(REAR, -1, KP * abs(target_angle[REAR] - curr_angle[REAR]))
            #drive_motor(FRONT, -1, KP * abs(target_angle[FRONT] - curr_angle[REAR]))   # because FRONT encoder is malfunction
            else:
                drive_motor(REAR, 0, 0)
                drive_motor(FRONT, 0, 0)
    print target_angle[REAR]

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
    global is_l_button_input
    global is_r_button_input
    global is_select_button_input

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

    if msg.axes[7] == -1.0:
        elevating_lift("down", 128)
    elif msg.axes[7] == 1.0:
        elevating_lift("up", 128)
    elif msg.axes[7] == 0:
        elevating_lift("stop", 0)

    if (msg.axes[4] >= JOY_BORDER and curr_angle[0] < ANGLE_LIMIT):
        drive_motor(REAR, -1, 100)
        drive_motor(FRONT, -1, 100)
    elif (msg.axes[4] <= -JOY_BORDER and curr_angle[0] > -ANGLE_LIMIT):
        drive_motor(REAR, 1, 100)
        drive_motor(FRONT, 1, 100)
    elif (msg.axes[4] < JOY_BORDER and msg.axes[4] > -JOY_BORDER):
        drive_motor(REAR, 0, 0)
        drive_motor(FRONT, 0, 0)

def sensor_callback(msg):
    global curr_angle
    curr_angle = msg.data
    print curr_angle

def subscriber():
    rospy.init_node("motor_drive_node")
    rospy.Subscriber("joy", Joy, joy_callback)
    rospy.Subscriber("sensor", Int32MultiArray, sensor_callback)
    rospy.spin()

if __name__ == '__main__':
    motor = [REAR, FRONT, LIFT, LEFT, RIGHT]
    for m in motor:
        init_output_pin(m)

    subscriber()
