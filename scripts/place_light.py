#!/usr/bin/env python

import rospy
import geometry_msgs.msg  


def place_light():

    rospy.init_node('place_light', anonymous=True)
    spub = rospy.Publisher('traffic_light_placement', geometry_msgs.msg.Twist, queue_size=10)
    
    msg=geometry_msgs.msg.Twist()
    
    rate = rospy.Rate(10) # 10hz
    
    while not rospy.is_shutdown():
        
        msg.linear.x=float(input("x location "))
        msg.linear.y=float(input("y location "))
        msg.linear.z=float(input("z location "))
        
        spub.publish(msg)
        
        rate.sleep()

if __name__ == '__main__':
    try:
        place_light()
    except rospy.ROSInterruptException:
        pass