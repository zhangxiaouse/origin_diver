#include "pub_steerfeedback.h"

namespace cyberc3 {
namespace pub {

SteerPub::SteerPub(const ros::NodeHandle &nh, const std::string &topic_name,
                   int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<cyber_msgs::SteerFeedback>(topic_name, buff_size);
}

void SteerPub::Publish(double steer_feedback, double speed_feedback,
                       double steerWheel2Dot, double time, const double ratio) {
  cyber_msgs::SteerFeedback steer_msg;
  double omega = 0, speed_mps = 0;
  steer_msg.header.stamp = ros::Time().fromSec(time);
  steer_msg.steer_0p1d = steer_feedback * ratio;
  speed_mps = speed_feedback / 100;
  omega =
      -sin(steer_feedback / 10 / 180 * 3.1415927) * speed_mps / steerWheel2Dot;
  steer_msg.steer_torque = omega;
  publisher_.publish(steer_msg);
}

void SteerPub::Publish(const cyberc3::feedback::steer &steerfeedback) {
  cyber_msgs::SteerFeedback steer_msg;

  publisher_.publish(steer_msg);
}

} // namespace pub
} // namespace cyberc3
