#pragma once

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

namespace cyberc3 {
namespace pub {
class MarkerPub {
private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;

public:
  MarkerPub(const ros::NodeHandle &nh, const std::string &topic_name,
            int buff_size);
  MarkerPub() = default;
  void Publish(double steer_feedback, double time);
};
} // namespace pub
} // namespace cyberc3