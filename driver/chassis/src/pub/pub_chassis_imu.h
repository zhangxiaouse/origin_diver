#pragma once

#include "geometry_msgs/Vector3Stamped.h"
#include <ros/ros.h>

namespace cyberc3 {
namespace pub {
class ChassisImuPub {
private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;

public:
  ChassisImuPub(const ros::NodeHandle &nh, const std::string &topic_name,
                int buff_size);
  ChassisImuPub() = default;
  void Publish(double time, double speed, double angle, double steerWheel2Dot);
};
} // namespace pub
} // namespace cyberc3