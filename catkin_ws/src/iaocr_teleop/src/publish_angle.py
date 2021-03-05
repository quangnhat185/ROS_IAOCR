#!/usr/bin/env python
# license removed for brevity

import rospy
from iaocr_teleop.msg import Angle


def publish_angle(speed):
    pub = rospy.Publisher('heading_angle', Angle, queue_size=10)
    rospy.init_node('angle_publisher', anonymous=True)
    rate = rospy.Rate(100) # 10hz

    while not rospy.is_shutdown():
        rospy.loginfo(" %i "%speed)
        pub.publish(speed)
        rate.sleep()

if __name__ == '__main__':
    speed = 250
    try:
        publish_angle(speed)
    except rospy.ROSInterruptException:
        pass
        