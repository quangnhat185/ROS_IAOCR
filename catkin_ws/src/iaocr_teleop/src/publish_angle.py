#!/usr/bin/env python
# license removed for brevity

import rospy
import numpy as np
from iaocr_teleop.msg import Angle
from sensor_msgs.msg import Joy

heading_angle = 0

gamepad_dic = {
    (0,1): 720,
    (1,0): 360,
    (1,1): 0
}

def angle_from_gamepad_event(axes_array, button_array):
    #rospy.loginfo(list(button_array).index(1))
    angle = int

    if (1 in button_array):
        angle = gamepad_dic[button_array]
    else:
        if (axes_array[0] == 0 and axes_array[1]==-1): angle = 1000
        else: angle = int(180/np.pi*(np.arctan2(axes_array[0],axes_array[1]))+ 180)

    #rospy.loginfo(angle)       
    return angle

def callback(data):
    # Left joystick 
    #rospy.loifginfo("%.3f -  %.3f"%(data.axes[0], data.axes[1]))

    # LB and RB
    # rospy.loginfo("%i -  %i"%(data.buttons[4], data.buttons[5]))
    #rospy.loginfo(data.axes[:2])
    
    # Derive angle from gamepad signal
    global heading_angle
    heading_angle = angle_from_gamepad_event(data.axes[:2],data.buttons[4:6])

def main():
    # init node
    rospy.init_node('angle_publisher', anonymous=True)
    # subcribe gamepad topic
    rospy.Subscriber("/joy", Joy, callback)

    # publush heading angle
    pub = rospy.Publisher('heading_angle', Angle, queue_size=10)
    rate = rospy.Rate(10) # 10hz


    while not rospy.is_shutdown():
        pub.publish(heading_angle)
        rospy.loginfo("publisher: %i" %heading_angle)
        rate.sleep()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
        