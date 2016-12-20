#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include "sound_play/sound_play.h"
std::string path_to_sounds;

class sound{
private:
  sound_play::SoundClient sc;

public:
  void Callback(const std_msgs::Int8::ConstPtr& msg) {
    ros::Rate loop_rate(0.5);
    switch (msg ->data) {
      case 1:
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
    } // End of switch.
    loop_rate.sleep();
  } // End of void Callback.

}; // End of sound class.

int main (int argc, char* argv[])
{
ros::init(argc, argv, "subscriber_node");
ros::NodeHandle n;
sound music;
path_to_sounds = "/home/oliver/ros_ws/src/guidebot/piano/";
ros::Subscriber sub = n.subscribe("depth_value", 1, &sound::Callback, &music);
ros::spin();
return 0;
} // End of int main. 
