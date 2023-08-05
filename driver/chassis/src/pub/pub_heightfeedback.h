#pragma once
#include "std_msgs/Int32.h"
#include <ros/ros.h>

namespace cyberc3 {
namespace pub {
    class IheightPub {
    private:
        ros::NodeHandle nh_;
        ros::Publisher publisher_;

    public:
        IheightPub(const ros::NodeHandle &nh,
                   const std::string &topic_name,
                   int buff_size);
        IheightPub() = default;
        void Publish(int32_t height, double time);
    };

}  // namespace pub
}  // namespace cyberc3