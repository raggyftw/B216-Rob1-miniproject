#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include "sound_play/sound_play.h"
std::string path_to_sounds;

class chatter{
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
        }
        loop_rate.sleep();
      }

};

int main (int argc, char* argv[])
{
ros::init(argc, argv, "subscriber_node");
ros::NodeHandle n;
chatter music;
path_to_sounds = "/home/oliver/ros_ws/src/guidebot/piano/";
ros::Subscriber sub = n.subscribe("chatter", 1, &chatter::Callback, &music);
ros::spin();

return 0;
}
