#pragma once

#include <ros/ros.h>

#include "../forklift/data/feedback/steer.h"
#include "cyber_msgs/SteerFeedback.h"
namespace cyberc3 {
namespace pub {
class SteerPub {
private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;

public:
  SteerPub(const ros::NodeHandle &nh, const std::string &topic_name,
           int buff_size);
  SteerPub() = default;
  void Publish(double steer_feedback, double speed_feedback,
               double steerWheel2Dot, double time, const double ratio);
  void Publish(const cyberc3::feedback::steer &steerfeedback);
};
} // namespace pub
} // namespace cyberc3