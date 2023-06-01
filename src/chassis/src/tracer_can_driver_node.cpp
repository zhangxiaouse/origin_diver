#include "tracer_can_driver_node.h"

namespace cyberc3
{
  namespace node
  {
    tracer_can_driver_node::tracer_can_driver_node(const ros::NodeHandle &nh,
                                                   const ros::NodeHandle &pnh)
        : nh_(nh), pnh_(pnh)
    {
      can_bridge_ptr_.reset(new cyber_c3::can_bridge::lcan(false));
      tracer_ptr_ = std::make_shared<cyberc3::vehicle::tracer>();
    }

    void tracer_can_driver_node::receive()
    {
      cyberc3::basic::can thiscan;
      for (size_t i = 0; i < 8; i++)
      {
        thiscan.data[i] = 0;
      }

      uint16_t can_frame_[10] = {};
      double time_;
      int received_can_frame = 0;
      while (1)
      {
        usleep(100); // 0.1ms = 10000hz
        received_can_frame = can_bridge_ptr_->Read(thiscan);
        if (received_can_frame == 0)
        {
          continue;
        }
        can_frame_[0] = thiscan.id;
        can_frame_[1] = thiscan.len;
        for (size_t i = 2; i < 10; i++)
        {
          can_frame_[i] = thiscan.data[i - 2];
        }
        // time_ = ros::Time::now().nsec;
        // array_pub_ptr_->Publish(can_frame_, 10, 1);
        // for (auto n : autotrike_ptr_->WhiteList)
        // {
        //   if (n == thiscan.id)
        //   {
        //     autotrike_ptr_->Decode(thiscan, ros::Time::now().toSec(),
        //                            param_steer_null_point, car.speed_feedback_,
        //                            car.steer_feedback_, brake_position,
        //                            motor_error);
        //     break;
        //   }
        // }
      }
    }

    // void tracer_can_driver_node::Timer20hzCallback(const ros::TimerEvent &)
    // {
    // }

    // void tracer_can_driver_node::Timer50hzCallback(const ros::TimerEvent &)
    // {
    // }
  } // namespace node
} // namespace cyberc3

int main(int argc, char **argv)
{
  ros::init(argc, argv, "VehicleCanNode");
  ros::NodeHandle nh_;
  ros::NodeHandle pnh_("~");
  cyberc3::node::tracer_can_driver_node tracer_can_driver_node_(nh_, pnh_);
  std::thread receive_thread(&cyberc3::node::tracer_can_driver_node::receive,
                             std::ref(tracer_can_driver_node_));
  ros::spin();
}