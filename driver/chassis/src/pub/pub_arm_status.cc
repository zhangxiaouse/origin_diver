#include "pub_arm_status.h"
#include "std_msgs/Int8.h"

namespace cyberc3 {
namespace pub {
    IarmStatusPub::IarmStatusPub(const ros::NodeHandle &nh,
                                 const std::string &topic_name,
                                 int buff_size)
      : nh_(nh) {
        publisher_ = nh_.advertise<std_msgs::Int8>(topic_name, buff_size);
    }

    void IarmStatusPub::Publish_scaling_status(bool scaling_status_push,
                                               bool scaling_status_pull,
                                               double time) {
        std_msgs::Int8 data_;
        if (scaling_status_push == 1) {
            data_.data = 1;
        } else if (scaling_status_pull == 1) {
            data_.data = 2;
        } else {
            data_.data = 3;
        }
        publisher_.publish(data_);
    }
    void IarmStatusPub::Publish_height_status(bool height_status_down,
                                              bool height_status_up,
                                              double time) {
        std_msgs::Int8 data_;
        if (height_status_down == 1) {
            data_.data = 1;
        } else if (height_status_up == 1) {
            data_.data = 2;
        } else {
            data_.data = 3;
        }
        publisher_.publish(data_);
    }
    void IarmStatusPub::Publish_pitching_status(bool pitching_status_forward,
                                                bool pitching_status_backward,
                                                double time) {
        std_msgs::Int8 data_;
        if (pitching_status_forward == 1) {
            data_.data = 1;
        } else if (pitching_status_backward == 1) {
            data_.data = 2;
        } else {
            data_.data = 3;
        }
        publisher_.publish(data_);
    }

}  // namespace pub
}  // namespace cyberc3