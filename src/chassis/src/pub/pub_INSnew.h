
#pragma once

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <tf/transform_datatypes.h> // tf::createQuaternionMsgFromRollPitchYaw

#include "gnss_data.h"
#include "imu_data.h"

namespace cyberc3 {
namespace can {
class imu {
public:
  imu(const ros::NodeHandle &nh, const std::string &topic_name, int buff_size);
  imu() = default;
  void Publish(cyberc3::data::IMUData &imu_data);

private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;
};

class gnss {
public:
  gnss(const ros::NodeHandle &nh, const std::string &topic_name, int buff_size);
  gnss() = default;
  void Publish(cyberc3::data::GNSSData &gnss_data);

private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;
};

} // namespace can
} // namespace cyberc3