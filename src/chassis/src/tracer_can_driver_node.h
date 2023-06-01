#include "tracer/tracer.h"
#include "cyber_msgs/CanFrame.h"
#include "lcan/lcan.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int32.h"
#include <ros/ros.h>
#include <thread>

namespace cyberc3
{
  namespace node
  {
    class tracer_can_driver_node
    {
    public:
      std::shared_ptr<cyber_c3::can_bridge::interface> can_bridge_ptr_;
      std::shared_ptr<cyberc3::vehicle::tracer> tracer_ptr_;

      // std::shared_ptr<cyberc3::pub::SpeedPub> speed_pub_ptr_;
      // std::shared_ptr<cyberc3::pub::SteerPub> steer_pub_ptr_;
      // std::shared_ptr<cyberc3::pub::arrayPub> array_pub_ptr_;
      // ros::Timer timer_20hz_;
      // ros::Timer timer_50hz_;

    private:
      ros::NodeHandle nh_;
      ros::NodeHandle pnh_;
      // ros::Publisher __pub_test_data_;

    public:
      tracer_can_driver_node(const ros::NodeHandle &nh,
                             const ros::NodeHandle &pnh);
      ~tracer_can_driver_node(){};
      void receive();
      // void Timer20hzCallback(const ros::TimerEvent &);
      // void Timer50hzCallback(const ros::TimerEvent &);
    };
  }
}