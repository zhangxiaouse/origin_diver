#include "pub_body_status.h"

namespace cyberc3 {
namespace pub {
IbodyStatusPub::IbodyStatusPub(const ros::NodeHandle &nh,
                               const std::string &topic_name, int buff_size)
    : nh_(nh) {
  publisher_ =
      nh_.advertise<cyber_msgs::body_status_feedback>(topic_name, buff_size);
}

void IbodyStatusPub::Publish_body_status(
    const cyberc3::feedback::car_state carState, double time) {
  cyber_msgs::body_status_feedback data_;
  data_.is_auto_drive = carState.is_auto;
  data_.is_emergency_stop = carState.is_emergency;
  data_.is_start_button_on = carState.is_start;
  data_.is_stop_button_on = carState.is_stop;
  publisher_.publish(data_);
}
} // namespace pub
} // namespace cyberc3