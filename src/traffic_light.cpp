#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <tf/transform_broadcaster.h>


int state=1;
geometry_msgs::Twist location;

bool light_blink = false;
bool light1_blink =false;
int blink_hz=10;

void set_state(const geometry_msgs::Vector3& msg)
{
    if (msg.x>0)
    {
        state=3;
        blink_hz=msg.x;
    }
    else if ((msg.z>0)&&(msg.y>0))
    {
        state=2;
        blink_hz=msg.y;
    }
    else if(msg.z>0)
    {
        state=1;
        blink_hz=msg.z;
    }
    else if(msg.y>0)
    {
        state=4;
        blink_hz=msg.y;
    }

    if (blink_hz!=1)
    {
        light_blink=(state!=2);
        light1_blink=(state==2);
    }
    else
    {
        light_blink=false;
        light1_blink=false;
        blink_hz=10;
    }
}

void change_placement(const geometry_msgs::Twist& msg)
{
    location=msg;
}

int main( int argc, char** argv )
{
    bool substate_light1 = true;
    bool substate_light =false;

    location.linear.x=0;
    location.linear.y=0;
    location.linear.z=0;
    
    ros::init(argc, argv, "traffic_light");
    ros::NodeHandle n;
       
    ros::Publisher box_marker_pub = n.advertise<visualization_msgs::Marker>("traffic_light", 100);
    ros::Publisher light_marker_pub = n.advertise<visualization_msgs::Marker>("traffic_light", 100);
    ros::Publisher light1_marker_pub = n.advertise<visualization_msgs::Marker>("traffic_light", 100);
    
    ros::Subscriber sub1 = n.subscribe("traffic_light_state", 1000,set_state);
    ros::Subscriber sub2 = n.subscribe("traffic_light_placement", 1000,change_placement);
    
    visualization_msgs::Marker box_marker;
    visualization_msgs::Marker light_marker;
    visualization_msgs::Marker light1_marker;
            
    while(ros::ok)
    {
    
    ros::Rate rate(blink_hz);

    light1_marker.header.frame_id = "traffic_light";
    light1_marker.header.stamp = ros::Time::now();
    
    light_marker.header.frame_id = "traffic_light";
    light_marker.header.stamp = ros::Time::now();

    box_marker.header.frame_id = "traffic_light";
    box_marker.header.stamp = ros::Time::now();
        
    box_marker.ns = "box";
    box_marker.id = 0;

    box_marker.type = visualization_msgs::Marker::MESH_RESOURCE;

    box_marker.action = visualization_msgs::Marker::ADD;

    box_marker.pose.position.x = 0;
    box_marker.pose.position.y = 0;
    box_marker.pose.position.z = 0;

    box_marker.pose.orientation.x = 1;
    box_marker.pose.orientation.y = 0;
    box_marker.pose.orientation.z = 0;
    box_marker.pose.orientation.w = 1;

    box_marker.scale.x = 0.01;
    box_marker.scale.y = 0.01;
    box_marker.scale.z = 0.01;

    box_marker.color.r = 0.5f;
    box_marker.color.g = 0.5f;
    box_marker.color.b = 0.5f;
    box_marker.color.a = 1.0;

    box_marker.lifetime = ros::Duration();

    box_marker.mesh_resource = "package://traffic_light/stl/box.stl";

    light_marker.ns = "light1";
    light_marker.id = 1;

    light_marker.type = visualization_msgs::Marker::MESH_RESOURCE;

    light_marker.action = visualization_msgs::Marker::ADD;

    light_marker.color.b = 0.0f;
    light_marker.color.a = 1.0;

    light_marker.mesh_resource = "package://traffic_light/stl/light.stl";
    
    light_marker.pose.position.x = 0;
    light_marker.pose.position.y = -0.001;

    light_marker.pose.orientation.x = 1;
    light_marker.pose.orientation.y = 0;
    light_marker.pose.orientation.z = 0;
    light_marker.pose.orientation.w = 1;

    light_marker.scale.x = 0.01;
    light_marker.scale.y = 0.01;
    light_marker.scale.z = 0.01;

    light1_marker.ns = "light2";
    light1_marker.id = 2;
    light1_marker.type = visualization_msgs::Marker::MESH_RESOURCE;

    light1_marker.action = visualization_msgs::Marker::ADD;

    light1_marker.pose.position.x = 0;
    light1_marker.pose.position.y = -0.001;
    light1_marker.pose.position.z = 0.1;

    light1_marker.pose.orientation.x = 1;
    light1_marker.pose.orientation.y = 0;
    light1_marker.pose.orientation.z = 0;
    light1_marker.pose.orientation.w = 1;

    light1_marker.color.r = 0.5f;
    light1_marker.color.g = 0.5f;
    light1_marker.color.b = 0.5f;
    light1_marker.color.a = 1.0f;

    light1_marker.scale.x = 0.01;
    light1_marker.scale.y = 0.01;
    light1_marker.scale.z = 0.01;
    
    light1_marker.mesh_resource = "package://traffic_light/stl/light1.stl";

    switch (state){
        {case 1:
            light_marker.color.r = 1.0f;
            light_marker.color.g = 0.0f;
            light_marker.pose.position.z = 0.2;
        break;}
        {case 2:
            light_marker.color.r = 1.0f;
            light_marker.color.g = 0.0f;
            light_marker.pose.position.z = 0.2;
        break;}
        {case 3:
            light_marker.color.r = 0.0f;
            light_marker.color.g = 1.0f;
            light_marker.pose.position.z = 0.0;
        break;}
        {case 4:
            light_marker.color.r = 1.0f;
            light_marker.color.g = 1.0f;
            light_marker.pose.position.z = 0.1;
        break;}
    }
    if (state==2)
    {
        if ((substate_light1 == false)||(light1_blink==false))
            {     
            light1_marker.color.r = 1.0f;
            light1_marker.color.g = 1.0f;
            light1_marker.color.b = 0.0f;
            substate_light1 = true;
        }
        else
        {
            substate_light1 = false;
        }
    }
    else if(light_blink==true)
    {   
        if(substate_light==false)
        {
            substate_light = true;
            light_marker.color.r = 0.5f;
            light_marker.color.g = 0.5f;
            light_marker.color.b = 0.5f;           
        }
        else
        {
            substate_light = false;
        }
    }

    light_marker.lifetime = ros::Duration();
    light1_marker.lifetime = ros::Duration();
    box_marker.lifetime = ros::Duration();

    light1_marker_pub.publish(light1_marker);
    box_marker_pub.publish(box_marker);
    light_marker_pub.publish(light_marker);

    static tf::TransformBroadcaster br;
    tf::Transform transform;
    
    transform.setOrigin( tf::Vector3(location.linear.x,location.linear.y,location.linear.z) );
    transform.setRotation(tf::Quaternion(0,0,0,1));
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "traffic_light", "map"));
    
    ros::spinOnce();
    rate.sleep();
    }
}