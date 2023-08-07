#include "pub_ican4055.h"

namespace cyberc3 {
namespace pub {
    Ican4055Pub::Ican4055Pub(const ros::NodeHandle &nh,
                             const std::string &topic_name,
                             int buff_size)
      : nh_(nh) {
        publisher_ =
          nh_.advertise<std_msgs::UInt8MultiArray>(topic_name, buff_size);
    }

    void Ican4055Pub::Publish(char ButtonState, double time) {
        std_msgs::UInt8MultiArray data_;
        for (char count = 0; count <= 7; count++) {
            data_.data.push_back((ButtonState >> count) & 0b01);
        }
        publisher_.publish(data_);
    }
}  // namespace pub
}  // namespace cyberc3