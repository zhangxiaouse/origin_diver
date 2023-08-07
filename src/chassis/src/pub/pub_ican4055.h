#pragma once
#include "std_msgs/UInt8MultiArray.h"
#include <ros/ros.h>
namespace cyberc3 {
namespace pub {
    class Ican4055Pub {
    private:
        ros::NodeHandle nh_;
        ros::Publisher publisher_;

    public:
        Ican4055Pub(const ros::NodeHandle &nh,
                    const std::string &topic_name,
                    int buff_size);
        Ican4055Pub() = default;
        void Publish(char ButtonState, double time);
    };

}  // namespace pub
}  // namespace cyberc3
