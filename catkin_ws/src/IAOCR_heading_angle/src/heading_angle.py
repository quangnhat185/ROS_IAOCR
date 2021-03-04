#!/usr/bin/env python
# license removed for brevity

import rospy
from Angle.msg import angle

def publish_angle():
    pub = rospy.Publisher('heading_angle', angle, queue_size=10)
    rospy.init_node('angle_publisher', anonymous=True)
    rate = rospy.Rate(10) # 10hz


while not rospy.is_shutdown():
    i = 0
    if (i==360): i=0
    i++
    rospy.loginfo(" %i degree"%i)
    pub.publish(i)
    rate.sleep()

if __name__ == '__main__':
    try:
        publish_angle()
        except rospy.ROSInterruptException:
    pass