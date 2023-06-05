#include "tracer/tracer.h"
#include "cyber_msgs/CanFrame.h"
#include "cyber_msgs/AGVSpeedFeedback.h"
#include "cyber_msgs/AGVSpeedCmd.h"
#include "lcan/lcan.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int32.h"
#include <ros/ros.h>
#include <thread>
#include "pub/pub_array.h"
#include "tracer/data/feedback/feedback_tracer.h"
#include "tracer/data/command/tracer_command.h"

namespace cyberc3
{
  namespace node
  {
    class tracer_can_driver_node
    {
    public:
      std::shared_ptr<cyber_c3::can_bridge::interface> can_bridge_ptr_;
      std::shared_ptr<cyberc3::vehicle::tracer> tracer_ptr_;
      cyberc3::feedback::tracer tracer_feedback_ptr_;
      cyberc3::command::tracer_command tracer_command_ptr_;
      std::shared_ptr<cyberc3::pub::arrayPub> array_pub_ptr_;
      ros::Timer timer_50hz_;

    private:
      double v_ = 0;
      double r_ = 0;
      double d_ = 0.269;

      ros::NodeHandle nh_;
      ros::NodeHandle pnh_;
      cyber_msgs::AGVSpeedFeedback agv_speed_feedback_;
      cyber_msgs::AGVSpeedCmd agv_speed_cmd_;
      ros::Publisher publish_vehicle_speed_;
      ros::Subscriber subscriber_agv_speed_;

      double left_speed = 0;
      double right_speed = 0;

    public:
      tracer_can_driver_node(const ros::NodeHandle &nh, const ros::NodeHandle &pnh);
      ~tracer_can_driver_node(){};
      void receive();
      void Timer50hzCallback(const ros::TimerEvent &);
      void speed_msg_callback(const cyber_msgs::AGVSpeedCmd msg);
    };
  }
}