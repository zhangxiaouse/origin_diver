#include "pub_speedfeedback.h"

namespace cyberc3 {
namespace pub {

SpeedPub::SpeedPub(const ros::NodeHandle &nh, const std::string &topic_name,
                   int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<cyber_msgs::SpeedFeedback>(topic_name, buff_size);
}

void SpeedPub::Publish(double speed_feedback, double time, double ratio) {
  cyber_msgs::SpeedFeedback speed_msg;
  speed_msg.header.stamp = ros::Time().fromSec(time);
  speed_msg.speed_cmps = speed_feedback * ratio;
  speed_msg.speed_kmph = speed_feedback * 36 / 1000;
  publisher_.publish(speed_msg);
}

void SpeedPub::Publish(const cyberc3::feedback::speed &speedfeedback) {
  cyber_msgs::SpeedFeedback speed_msg;

  publisher_.publish(speed_msg);
}

} // namespace pub

} // namespace cyberc3
