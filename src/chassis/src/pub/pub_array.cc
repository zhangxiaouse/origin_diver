#include "pub_array.h"
#include "std_msgs/UInt16MultiArray.h"
namespace cyberc3 {
namespace pub {
arrayPub::arrayPub(const ros::NodeHandle &nh, const std::string &topic_name,
                   int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<std_msgs::UInt16MultiArray>(topic_name, buff_size);
}

void arrayPub::Publish(const uint16_t ar[], uint16_t len, double time) {
  std_msgs::UInt16MultiArray msg;
  for (size_t i = 0; i < 10; i++) {
    msg.data.push_back(ar[i]);
  }
  publisher_.publish(msg);
}
} // namespace pub
} // namespace cyberc3
