#include "pub_chassis_imu.h"

namespace cyberc3 {
namespace pub {

ChassisImuPub::ChassisImuPub(const ros::NodeHandle &nh,
                             const std::string &topic_name, int buff_size)
    : nh_(nh) {
  publisher_ =
      nh_.advertise<geometry_msgs::Vector3Stamped>(topic_name, buff_size);
}

void ChassisImuPub::Publish(double time, double speed_cmps, double angle_0p1d,
                            double steerWheel2Dot) {
  geometry_msgs::Vector3Stamped msg;
  double omega_ = 0, speed_mps_ = 0, steed_0p1d_ = 0;
  msg.header.stamp = ros::Time().fromSec(time);
  msg.vector.x = 0;
  msg.vector.y = 0;
  speed_mps_ = speed_cmps / 100;
  if (speed_mps_ > 0) {
    if (steerWheel2Dot != 0) {
      omega_ =
          sin(angle_0p1d / 10 / 180 * 3.1415927) * speed_mps_ / steerWheel2Dot;
    } else {
      omega_ = 0;
    }
  } else if (speed_mps_ < 0) {
    if (steerWheel2Dot != 0) {
      omega_ =
          sin(angle_0p1d / 10 / 180 * 3.1415927) * speed_mps_ / steerWheel2Dot;
    } else {
      omega_ = 0;
    }
  } else {
    omega_ = 0;
  }
  msg.vector.z = omega_;
  publisher_.publish(msg);
}

} // namespace pub
} // namespace cyberc3
