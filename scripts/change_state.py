#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import geometry_msgs.msg  

def talker():

    pub = rospy.Publisher('traffic_light_state', geometry_msgs.msg.Vector3, queue_size=10)
    rospy.init_node('change_state', anonymous=True)
    
    rate = rospy.Rate(10) # 10hz
    
    while not rospy.is_shutdown():
        
        msg=geometry_msgs.msg.Vector3()
        msg.x=int(input("green_sate="))
        msg.y=int(input("yellow_state="))
        msg.z=int(input("red_state="))
        print("\n")

        pub.publish(msg)
        
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass