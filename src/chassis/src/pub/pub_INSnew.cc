#include "pub_INSnew.h"

namespace cyberc3 {
namespace can {

imu::imu(const ros::NodeHandle &nh, const std::string &topic_name,
         int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<sensor_msgs::Imu>(topic_name, buff_size);
}

void imu::Publish(cyberc3::data::IMUData &imu_data) {
  sensor_msgs::Imu thisImu;

  thisImu.linear_acceleration.x = imu_data.linear_acceleration.x;
  thisImu.linear_acceleration.y = imu_data.linear_acceleration.y;
  thisImu.linear_acceleration.z = imu_data.linear_acceleration.z;
  thisImu.angular_velocity.x = imu_data.angular_velocity.x;
  thisImu.angular_velocity.y = imu_data.angular_velocity.y;
  thisImu.angular_velocity.z = imu_data.angular_velocity.z;
  thisImu.orientation = tf::createQuaternionMsgFromRollPitchYaw(
      imu_data.rpy.roll, imu_data.rpy.pitch, imu_data.rpy.yaw);
  thisImu.header.stamp = ros::Time().fromSec(imu_data.time);

  publisher_.publish(thisImu);
}

gnss::gnss(const ros::NodeHandle &nh, const std::string &topic_name,
           int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<sensor_msgs::NavSatFix>(topic_name, buff_size);
}

void gnss::Publish(cyberc3::data::GNSSData &gnss_data) {
  sensor_msgs::NavSatFix thisnav;

  thisnav.altitude = gnss_data.altitude;
  thisnav.latitude = gnss_data.latitude;
  thisnav.longitude = gnss_data.longitude;
  thisnav.header.stamp = ros::Time().fromSec(gnss_data.time);
  thisnav.status.service = gnss_data.gps_num;

  if (gnss_data.position_init_status >= 48) {
    thisnav.status.status = 4;
  } else if (31 < gnss_data.position_init_status &&
             gnss_data.position_init_status < 35) {
    thisnav.status.status = 5;
  } else if (16 < gnss_data.position_init_status &&
             gnss_data.position_init_status < 19) {
    thisnav.status.status = 3;
  } else if (gnss_data.position_init_status == 16) {
    thisnav.status.status = 2;
  } else {
    thisnav.status.status = 1;
  }

  publisher_.publish(thisnav);
}

} // namespace can
} // namespace cyberc3