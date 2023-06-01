#pragma once

#include <ros/ros.h>

#include "../forklift/data/feedback/speed.h"
#include "cyber_msgs/SpeedFeedback.h"
namespace cyberc3 {
namespace pub {
class SpeedPub {
private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;

public:
  SpeedPub(const ros::NodeHandle &nh, const std::string &topic_name,
           int buff_size);
  SpeedPub() = default;
  void Publish(double speed_feedback, double time, double ratio);
  void Publish(const cyberc3::feedback::speed &speedfeedback);
};
} // namespace pub
} // namespace cyberc3