#include "tracer/tracer.h"
#include "cyber_msgs/CanFrame.h"
#include "cyber_msgs/AGVSpeedFeedback.h"
#include "lcan/lcan.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int32.h"
#include <ros/ros.h>
#include <thread>
#include "pub/pub_array.h"

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
      std::shared_ptr<cyberc3::pub::arrayPub> array_pub_ptr_;
      ros::Timer timer_50hz_;

    private:
      ros::NodeHandle nh_;
      ros::NodeHandle pnh_;
      cyber_msgs::AGVSpeedFeedback agv_speed_feedback_;
      ros::Publisher publish_vehicle_speed_;

    public:
      tracer_can_driver_node(const ros::NodeHandle &nh, const ros::NodeHandle &pnh);
      ~tracer_can_driver_node(){};
      void receive();
      void Timer50hzCallback(const ros::TimerEvent &);
    };
  }
}