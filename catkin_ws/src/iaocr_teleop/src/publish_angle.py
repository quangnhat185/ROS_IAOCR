#!/usr/bin/env python
# license removed for brevity

import rospy
from iaocr_teleop.msg import Angle

def publish_angle():
    pub = rospy.Publisher('heading_angle', Angle, queue_size=10)
    rospy.init_node('angle_publisher', anonymous=True)
    rate = rospy.Rate(50) # 10hz

    i = 0
    while not rospy.is_shutdown():
        if (i==360): i=0 
        i+=1
        rospy.loginfo(" %i degree"%i)
        pub.publish(i)
        rate.sleep()

if __name__ == '__main__':
    try:
        publish_angle()
    except rospy.ROSInterruptException:
        pass