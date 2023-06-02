#include "pub_INSold.h"

namespace cyberc3 {
namespace can {

// old imu vel
imu_angularvelocity::imu_angularvelocity(const ros::NodeHandle &nh,
                                         const std::string &topic_name,
                                         int buff_size)
    : nh_(nh) {
  publisher_ =
      nh_.advertise<geometry_msgs::Vector3Stamped>(topic_name, buff_size);
}

void imu_angularvelocity::Publish(cyberc3::data::IMUData &imu_data) {
  geometry_msgs::Vector3Stamped this_angularV;

  this_angularV.vector.x = imu_data.angular_velocity.x;
  this_angularV.vector.y = imu_data.angular_velocity.y;
  this_angularV.vector.z = -imu_data.angular_velocity.z;

  this_angularV.header.stamp = ros::Time().fromSec(imu_data.time);

  publisher_.publish(this_angularV);
}

// old gps heading
gps_heading::gps_heading(const ros::NodeHandle &nh,
                         const std::string &topic_name, int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<cyber_msgs::Heading>(topic_name, buff_size);
}

void gps_heading::Publish(cyberc3::data::IMUData &imu_data) {
  cyber_msgs::Heading this_heading;

  this_heading.data = imu_data.rpy.yaw;
  this_heading.std_dev = 0;
  this_heading.header.stamp = ros::Time().fromSec(imu_data.time);

  publisher_.publish(this_heading);
}
// old  gps_rawdata
gps_rawdata::gps_rawdata(const ros::NodeHandle &nh,
                         const std::string &topic_name, int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<cyber_msgs::GPGGA_MSG>(topic_name, buff_size);
}

void gps_rawdata::Publish(cyberc3::data::GNSSData &gnss_data) {
  cyber_msgs::GPGGA_MSG this_rawdata;

  this_rawdata.num_satellites = gnss_data.gps_num;
  if (gnss_data.position_init_status >= 48) {
    this_rawdata.status = 4;
  } else if (31 < gnss_data.position_init_status &&
             gnss_data.position_init_status < 35) {
    this_rawdata.status = 5;
  } else if (16 < gnss_data.position_init_status &&
             gnss_data.position_init_status < 19) {
    this_rawdata.status = 3;
  } else if (gnss_data.position_init_status == 16) {
    this_rawdata.status = 2;
  } else {
    this_rawdata.status = 1;
  }
  this_rawdata.header.stamp = ros::Time().fromSec(gnss_data.time);

  publisher_.publish(this_rawdata);
}

} // namespace can
} // namespace cyberc3
