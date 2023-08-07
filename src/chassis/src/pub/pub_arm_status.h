#pragma once

#include <ros/ros.h>

namespace cyberc3 {
namespace pub {
    class IarmStatusPub {
    private:
        ros::NodeHandle nh_;
        ros::Publisher publisher_;

    public:
        IarmStatusPub(const ros::NodeHandle &nh,
                      const std::string &topic_name,
                      int buff_size);
        IarmStatusPub() = default;
        void Publish_scaling_status(bool scaling_status_push,
                                    bool scaling_status_pull,
                                    double time);
        void Publish_height_status(bool height_status_up,
                                   bool height_status_down,
                                   double time);
        void Publish_pitching_status(bool pitching_status_forward,
                                     bool pitching_status_backward,
                                     double time);
    };

}  // namespace pub
}  // namespace cyberc3