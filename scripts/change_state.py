#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def talker():

    pub = rospy.Publisher('traffic_light_state', String, queue_size=10)
    rospy.init_node('change_state', anonymous=True)
    
    rate = rospy.Rate(10) # 10hz
    
    while not rospy.is_shutdown():
        
        rospy.loginfo("enter state ")
        
        msg=raw_input()
        
        pub.publish(msg)
        
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass