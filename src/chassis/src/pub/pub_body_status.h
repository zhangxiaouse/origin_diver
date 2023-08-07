#pragma once

#include "../forklift/data/feedback/car_state.h"
#include "cyber_msgs/body_status_feedback.h"
#include <ros/ros.h>
namespace cyberc3 {
namespace pub {
class IbodyStatusPub {
private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;

public:
  IbodyStatusPub(const ros::NodeHandle &nh, const std::string &topic_name,
                 int buff_size);
  IbodyStatusPub() = default;
  void Publish_body_status(const cyberc3::feedback::car_state carState,
                           double time);
};
} // namespace pub
} // namespace cyberc3