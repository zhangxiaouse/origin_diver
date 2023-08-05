
#pragma once

#include <geometry_msgs/Vector3Stamped.h>
#include <ros/ros.h>
#include <tf/transform_datatypes.h> // tf::createQuaternionMsgFromRollPitchYaw

#include "gnss_data.h"
#include "imu_data.h"

#include "cyber_msgs/GPGGA_MSG.h"
#include "cyber_msgs/Heading.h"

namespace cyberc3 {
namespace can {

class imu_angularvelocity {
public:
  imu_angularvelocity(const ros::NodeHandle &nh, const std::string &topic_name,
                      int buff_size);
  imu_angularvelocity() = default;
  void Publish(cyberc3::data::IMUData &imu_data);

private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;
};

class gps_heading {
public:
  gps_heading(const ros::NodeHandle &nh, const std::string &topic_name,
              int buff_size);
  gps_heading() = default;
  void Publish(cyberc3::data::IMUData &imu_data);

private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;
};

class gps_rawdata {
public:
  gps_rawdata(const ros::NodeHandle &nh, const std::string &topic_name,
              int buff_size);
  gps_rawdata() = default;
  void Publish(cyberc3::data::GNSSData &gnss_data);

private:
  ros::NodeHandle nh_;
  ros::Publisher publisher_;
};

} // namespace can
} // namespace cyberc3
