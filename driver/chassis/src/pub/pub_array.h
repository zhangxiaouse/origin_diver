#pragma once

#include <ros/ros.h>

namespace cyberc3 {
namespace pub {
class arrayPub {
private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;

public:
  arrayPub(const ros::NodeHandle &nh, const std::string &topic_name,
           int buff_size);
  arrayPub() = default;
  void Publish(const uint16_t ar[], uint16_t len, double time);
};
} // namespace pub
} // namespace cyberc3