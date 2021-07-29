#!/usr/bin/env python

import rospy
import geometry_msgs.msg  
import tf

def place_light():

    rospy.init_node('place_light', anonymous=True)
    spub = rospy.Publisher('traffic_light_placement', geometry_msgs.msg.Pose, queue_size=10)
    
    msg=geometry_msgs.msg.Pose()
    
    rate = rospy.Rate(10) # 10hz
    
    while not rospy.is_shutdown():
        
        msg.position.x=float(input("x location "))
        msg.position.y=float(input("y location "))
        msg.position.z=float(input("z location "))
        
        angle = float(input("introduce the z angle "))
        qoat = tf.transformations.quaternion_from_euler(0,0,angle*3.14/180)
        msg.orientation.x = qoat[0] 
        msg.orientation.y = qoat[1] 
        msg.orientation.z = qoat[2] 
        msg.orientation.w = qoat[3] 
        
        spub.publish(msg)
        
        rate.sleep()

if __name__ == '__main__':
    try:
        place_light()
    except rospy.ROSInterruptException:
        pass