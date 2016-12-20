#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include "sound_play/sound_play.h"

// Declaring a constructor
class sound{
private:
  // Declaring a soundclient for use in the constructor
  sound_play::SoundClient sc;
  std::string path_to_sounds;

public:
  // Creating the callback function
  void Callback(const std_msgs::Int8::ConstPtr& msg) {
    // Setting the desired frequency
    ros::Rate loop_rate(0.5);
    // Initiating a switch statement
    switch (msg ->data) {
      case 1:
        // Use soundclient to play certain sound
        sc.playWave(path_to_sounds+"G.wav");
        break; 
      case 2:
        sc.playWave(path_to_sounds+"A.wav");
        break;
      case 3:
        sc.playWave(path_to_sounds+"B.wav");
        break;
      case 4:
        sc.playWave(path_to_sounds+"C.wav");
        break;
      case 5:
        sc.playWave(path_to_sounds+"D.wav");
        break;
      default: // Set error message if no case is satisfied
        ROS_INFO("Error, invalid distance!");
        break;
    } // End of switch.
    loop_rate.sleep();
  } // End of void Callback.

}; // End of sound class.

int main (int argc, char* argv[])
{
  // Here the publising queue for the publisher is set to 1.
  static const uint32_t ROS_QUEUE_PUB = 1;
  
  // initializing ros and naming the node.
  ros::init(argc, argv, "subscriber_node");
  // Creating nodehandler.
  ros::NodeHandle n;
  
  sound music; // Storing the sound class information in music.
  // Defining the absolute path to sound files
  std::path_to_sounds = "/home/oliver/ros_ws/src/guidebot/piano/";
  // Subscribing to the topic depth_value and return the callback from the constructor sound
  ros::Subscriber sub = n.subscribe("depth_value", ROS_QUEUE_SUB, &sound::Callback, &music);
  
  ros::spin();
  return 0;
} // End of int main. 
