#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>


int state=1;
geometry_msgs::Pose location;

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

void change_placement(const geometry_msgs::Pose& msg)
{
    location=msg;
}

int main( int argc, char** argv )
{
    
    bool substate_light1 = true;
    bool substate_light =false;
    int size=1;
    std::string frame[10]={"_frame_1","_frame_2","_frame_3","_frame_4","_frame_5","_frame_6","_frame_7","_frame_8","_frame_9","_frame_10"};

    location.position.x=0;
    location.position.y=0;
    location.position.z=0;
    
    ros::init(argc, argv, "traffic_light");
    ros::NodeHandle n;
    
    static tf::TransformBroadcaster br;    
    tf::Transform transform;

    ros::Publisher marker_pub = n.advertise<visualization_msgs::MarkerArray>("traffic_light", 100);
    ros::Subscriber sub1 = n.subscribe("traffic_light_state", 1000,set_state);
    ros::Subscriber sub2 = n.subscribe("traffic_light_placement", 1000,change_placement);
    
    visualization_msgs::MarkerArray box_markers,light_markers,light1_markers;
    
    box_markers.markers.resize(10);
    light_markers.markers.resize(10);
    light1_markers.markers.resize(10);
        
    for (int i=0;i<10;i++)
    {
        light1_markers.markers[i].header.frame_id = "traffic_light"+frame[i];
        light1_markers.markers[i].header.stamp = ros::Time::now();

        light_markers.markers[i].header.frame_id = "traffic_light"+frame[i];
        light_markers.markers[i].header.stamp = ros::Time::now();

        box_markers.markers[i].header.frame_id = "traffic_light"+frame[i];
        box_markers.markers[i].header.stamp = ros::Time::now();

        box_markers.markers[i].ns = "box"+frame[i];
        box_markers.markers[i].id = 0+i*3;

        box_markers.markers[i].type = visualization_msgs::Marker::MESH_RESOURCE;

        box_markers.markers[i].action = visualization_msgs::Marker::ADD;

        box_markers.markers[i].pose.position.x = 0;
        box_markers.markers[i].pose.position.y = 0;
        box_markers.markers[i].pose.position.z = 0;

        box_markers.markers[i].pose.orientation.x = 1;
        box_markers.markers[i].pose.orientation.y = 0;
        box_markers.markers[i].pose.orientation.z = 0;
        box_markers.markers[i].pose.orientation.w = 1;

        box_markers.markers[i].scale.x = 0.01;
        box_markers.markers[i].scale.y = 0.01;
        box_markers.markers[i].scale.z = 0.01;

        box_markers.markers[i].color.r = 0.5f;
        box_markers.markers[i].color.g = 0.5f;
        box_markers.markers[i].color.b = 0.5f;
        box_markers.markers[i].color.a = 0.0;

        box_markers.markers[i].lifetime = ros::Duration();

        box_markers.markers[i].mesh_resource = "package://traffic_light/stl/box.stl";

        light_markers.markers[i].ns = "light1"+frame[i];
        light_markers.markers[i].id = 1+3*i;

        light_markers.markers[i].type = visualization_msgs::Marker::MESH_RESOURCE;

        light_markers.markers[i].action = visualization_msgs::Marker::ADD;

        light_markers.markers[i].color.b = 0.0f;
        light_markers.markers[i].color.a = 0.0;

        light_markers.markers[i].mesh_resource = "package://traffic_light/stl/light.stl";

        light_markers.markers[i].pose.position.x = 0;
        light_markers.markers[i].pose.position.y = -0.001;

        light_markers.markers[i].pose.orientation.x = 1;
        light_markers.markers[i].pose.orientation.y = 0;
        light_markers.markers[i].pose.orientation.z = 0;
        light_markers.markers[i].pose.orientation.w = 1;

        light_markers.markers[i].scale.x = 0.01;
        light_markers.markers[i].scale.y = 0.01;
        light_markers.markers[i].scale.z = 0.01;

        light1_markers.markers[i].ns = "light2"+frame[i];
        light1_markers.markers[i].id = 2+3*i;
        light1_markers.markers[i].type = visualization_msgs::Marker::MESH_RESOURCE;

        light1_markers.markers[i].action = visualization_msgs::Marker::ADD;

        light1_markers.markers[i].pose.position.x = 0;
        light1_markers.markers[i].pose.position.y = -0.001;
        light1_markers.markers[i].pose.position.z = 0.1;

        light1_markers.markers[i].pose.orientation.x = 1;
        light1_markers.markers[i].pose.orientation.y = 0;
        light1_markers.markers[i].pose.orientation.z = 0;
        light1_markers.markers[i].pose.orientation.w = 1;

        light1_markers.markers[i].color.r = 0.5f;
        light1_markers.markers[i].color.g = 0.5f;
        light1_markers.markers[i].color.b = 0.5f;
        light1_markers.markers[i].color.a = 0.0f;

        light1_markers.markers[i].scale.x = 0.01;
        light1_markers.markers[i].scale.y = 0.01;
        light1_markers.markers[i].scale.z = 0.01;

        light1_markers.markers[i].mesh_resource = "package://traffic_light/stl/light.stl";

        light_markers.markers[i].lifetime = ros::Duration();
        light1_markers.markers[i].lifetime = ros::Duration();
        box_markers.markers[i].lifetime = ros::Duration();
    }
    while(ros::ok)
    {
    
    ros::Rate rate(blink_hz);

    visualization_msgs::MarkerArray buffer;
    buffer.markers.resize(size*3);
    
    for (int i=0;i<size;i++)
    {
        box_markers.markers[i].color.a = 1.0f;
        light1_markers.markers[i].color.a = 1.0f;
        light_markers.markers[i].color.a = 1.0f;
        
        switch (state){
        {case 1:
            light_markers.markers[i].color.r = 1.0f;
            light_markers.markers[i].color.g = 0.0f;
            light_markers.markers[i].pose.position.z = 0.2;
        break;}
        {case 2:
            light_markers.markers[i].color.r = 1.0f;
            light_markers.markers[i].color.g = 0.0f;
            light_markers.markers[i].pose.position.z = 0.2;
        break;}
        {case 3:
            light_markers.markers[i].color.r = 0.0f;
            light_markers.markers[i].color.g = 1.0f;
            light_markers.markers[i].pose.position.z = 0.0;
        break;}
        {case 4:
            light_markers.markers[i].color.r = 1.0f;
            light_markers.markers[i].color.g = 1.0f;
            light_markers.markers[i].pose.position.z = 0.1;
        break;}
        }
        if (state==2)
        {
        if ((substate_light1 == false)||(light1_blink==false))
            {     
            light1_markers.markers[i].color.r = 1.0f;
            light1_markers.markers[i].color.g = 1.0f;
            light1_markers.markers[i].color.b = 0.0f;
            substate_light1 = true;
        }
        else
        {
            light1_markers.markers[i].color.r = 0.5f;
            light1_markers.markers[i].color.g = 0.5f;
            light1_markers.markers[i].color.b = 0.5f;
            substate_light1 = false;
        }
        }
        else if(light_blink==true)
        {   
            if(substate_light==false)
            {
                substate_light = true;
                light_markers.markers[i].color.r = 0.5f;
                light_markers.markers[i].color.g = 0.5f;
                light_markers.markers[i].color.b = 0.5f;           
            }
        else
        {
            substate_light = false;
        }
        }
        light1_markers.markers[i].header.stamp = ros::Time::now();
        light_markers.markers[i].header.stamp = ros::Time::now();
        box_markers.markers[i].header.stamp = ros::Time::now();

        light_markers.markers[i].lifetime = ros::Duration();
        light1_markers.markers[i].lifetime = ros::Duration();
        box_markers.markers[i].lifetime = ros::Duration();

        buffer.markers[3*i]=light1_markers.markers[i];
        buffer.markers[3*i+1]=light_markers.markers[i];
        buffer.markers[3*i+2]=box_markers.markers[i];

        transform.setOrigin( tf::Vector3((location.position.x + 1),location.position.y,location.position.z) );
        transform.setRotation(tf::Quaternion(0,0,0,1));
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"/map","/traffic_light"+frame[i]));
    }
    
    marker_pub.publish(buffer);

    ros::spinOnce();
    rate.sleep();

    }
}