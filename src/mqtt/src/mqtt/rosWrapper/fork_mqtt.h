#pragma once
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "../forkmqtt/forkmqtt.h"
#include "iostream"
#include <unistd.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int8MultiArray.h>
#include <std_msgs/Bool.h>
#include "cyber_msgs/body_status_feedback.h"

using namespace std;

namespace cyberc3
{
  namespace mqtt
  {

    class ForkMqtt
    {
    private:
      double count;
      int stager_mode_;
      int is_auto = 0;
      std::string user_name_ = "";
      std::string vin_ = "";
      std::string user_pass_ = "";
      ros::NodeHandle nh_;
      ros::Timer timer_1hz_;
      class mqtt_client *iot_client;
      int rc;
      bool subscribed = false;

      void timer_1hz_callback(const ros::TimerEvent &);
      void stagerModeCallback(const std_msgs::Int8 &msg);
      void autoModeCallback(const cyber_msgs::body_status_feedback &msg);

      ros::Publisher pub_cmd_from_mqtt;
      ros::Publisher pub_work_positions_;
      ros::Publisher pub_work_unfork_positions_;
      ros::Publisher pub_upload_task_;
      ros::Publisher pub_test_task_;
      ros::Publisher pub_request_auto_;

      ros::Subscriber sub_upload_task_done;
      ros::Subscriber sub_stager_mode;
      ros::Subscriber sub_auto_mode;
      void uploadTaskCompleteCallback(const std_msgs::BoolConstPtr &msg);

    public:
      ForkMqtt(ros::NodeHandle nh);
      ~ForkMqtt();
    };

  }
}