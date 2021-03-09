#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Joy

'''Joy message
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
float32[] axes
int32[] buttons
'''

def callback(data):
    # Left joystick 
    #rospy.loginfo("%.3f -  %.3f"%(data.axes[0], data.axes[1]))

    # LB and RB
    rospy.loginfo("%i -  %i"%(data.buttons[4], data.buttons[5]))

    
def listener():
    rospy.init_node('gamepad_listener', anonymous=False)

    rospy.Subscriber("/joy", Joy, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()