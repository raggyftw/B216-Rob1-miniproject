#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/Int8.h>
#include "sound_play/sound_play.h"

// Creating a global ROS publisher to publish the depth distance.
ros::Publisher distance_pub;
// Creating our callback function.
void Depth_callback(const sensor_msgs::Image::ConstPtr& msg)
{
    // Declaring the variables needed in the function.
    float dist_val = 0; //Float variable to store the depth data in meters.
    
    try {
        // Declaring cv pointer and filling it with msg information.
        cv_bridge::CvImageConstPtr cv_ptr;
        cv_ptr = cv_bridge::toCvShare(msg);

        // Setting the global maximum for the data type.
        double max = 0.0;
        // Returning max value of the array.
        cv::minMaxLoc(cv_ptr->image, 0, &max, 0, 0);
        // Declaring the Mat matrix.
        cv::Mat normalized;
        // Here the mat matrix is normalized and converted so we can use the data in the matrix.
        cv_ptr->image.convertTo(normalized, CV_32F, 1.0/max, 0);
        // Stores the scan data in dist_val.
        dist_val = cv_ptr->image.at<float>( 239,319 );
        std_msgs::Int8 distance;
        if (dist_val <= 1) {
            distance.data = 1;
        }// End of if.
        else if(dist_val <= 2  ){
            distance.data = 2;
        }// End of else if.
        else if(dist_val <= 3 ){
            distance.data = 3;
        }// End of else if.
        else if(dist_val <= 4 ){
            distance.data = 4;
        }// End of else if.
        else if(dist_val <= 5 ){
            distance.data = 5;
        }// End of else if.
        ROS_INFO("%d", distance.data);
        distance_pub.publish(distance);
    }//End of try .
    // Here any exception are handled.
     catch (const cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }//End of catch.
}//End of Depth_callback.

int main(int argc, char* argv[])
{
    // Here the publising queue for the subscriber is set to 1000 and 1 for the publisher.
    static const uint32_t ROS_QUEUE_PUB = 1;
    static const uint32_t ROS_QUEUE_SUB = 1000;
    
    // initializing ros and naming the node.
    ros::init(argc, argv, "detection_node");
    // Creating nodehandler.
    ros::NodeHandle n;
    // Advertising our publisher to the desired topic so it can be accessed by the subscriber_node.
    distance_pub = n.advertise<std_msgs::Int8>("depth_value", ROS_QUEUE_PUB);
    // Creating another nodehandler for the subscriber.
    ros::NodeHandle nh;
    // Subscribing to the depth image and returning the callback.
    ros::Subscriber sub = nh.subscribe("camera/depth/image", ROS_QUEUE_SUB, Depth_callback);

    ros::spin();
    return 0;
}//End of main.
