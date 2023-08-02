#include "pub_heightfeedback.h"

namespace cyberc3 {
namespace pub {
    IheightPub::IheightPub(const ros::NodeHandle &nh,
                           const std::string &topic_name,
                           int buff_size)
      : nh_(nh) {
        publisher_ = nh_.advertise<std_msgs::Int32>(topic_name, buff_size);
    }

    void IheightPub::Publish(int32_t height, double time) {
        std_msgs::Int32 data_;
        data_.data = height;
        publisher_.publish(data_);
    }
}  // namespace pub
}  // namespace cyberc3