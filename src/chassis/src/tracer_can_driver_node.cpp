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
      array_pub_ptr_ = std::make_shared<cyberc3::pub::arrayPub>(nh_, "/tracer/can_data", 1);
      publish_vehicle_speed_ = nh_.advertise<cyber_msgs::AGVSpeedFeedback>("/tracer/speedback", 1);
      timer_50hz_ = nh_.createTimer(ros::Duration(0.02), &tracer_can_driver_node::Timer50hzCallback, this);
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
        time_ = ros::Time::now().nsec;
        array_pub_ptr_->Publish(can_frame_, 10, 1);
        for (auto n : tracer_ptr_->WhiteList)
        {
          if (n == thiscan.id)
          {
            tracer_ptr_->Decode(thiscan, ros::Time::now().toSec(), tracer_feedback_ptr_);

            break;
          }
        }
      }
    }

    // void tracer_can_driver_node::Timer20hzCallback(const ros::TimerEvent &)
    // {
    // }

    void tracer_can_driver_node::Timer50hzCallback(const ros::TimerEvent &)
    {
      agv_speed_feedback_.left_speed_mps = tracer_feedback_ptr_.speed;
      agv_speed_feedback_.right_speed_mps = tracer_feedback_ptr_.speed;
      publish_vehicle_speed_.publish(agv_speed_feedback_);
    }
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