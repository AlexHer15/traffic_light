# test
# traffic_light
 To start the mesh in rviz run rosrun traffic_light traffic_light\n
 To change it's state send a V3 where the first element is green secound is yellow and third is red trought the traffic_light_state topic (change_state.py allows u to send it by keyboard). Also if the number isn't 1 the color with blink with the frequency of that number.\n 
 To change it's position send a geometry_msg/Twist trought the traffic_light_state_placement topic (place_light.py allows u to send it by keyboard)
