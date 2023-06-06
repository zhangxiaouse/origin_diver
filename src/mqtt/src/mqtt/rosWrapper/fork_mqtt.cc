#include "fork_mqtt.h"

namespace cyberc3
{
  namespace mqtt
  {

    ForkMqtt::ForkMqtt(ros::NodeHandle nh) : nh_(nh)
    {
      nh_.param<string>("vin", vin_, "6d083020404070");
      nh_.param<string>("user_name", user_name_, "test");
      nh_.param<string>("user_pass", user_pass_, "123456");
      pub_cmd_from_mqtt = nh_.advertise<std_msgs::Int8>("/mqtt/cmd", 1);
      pub_work_positions_ = nh_.advertise<std_msgs::Int8MultiArray>("/mqtt/fork/positions", 1);
      pub_work_unfork_positions_ = nh_.advertise<std_msgs::Int8MultiArray>("/mqtt/fork/unfork_positions", 1);
      pub_upload_task_ = nh_.advertise<std_msgs::Bool>("/mqtt/fork/upload_task", 1);
      sub_upload_task_done = nh_.subscribe("/mqtt/fork/upload_task/done", 5, &ForkMqtt::uploadTaskCompleteCallback, this);
      sub_stager_mode = nh_.subscribe("/stager_mode", 5, &ForkMqtt::stagerModeCallback, this);
      //  nh_->advertise<std_msgs::Int8>("/stager_mode", 1);
      sub_auto_mode = nh_.subscribe("/chassis/body_status_feedback", 5, &ForkMqtt::autoModeCallback, this);

      // /chassis/body_status_feedback
      mosqpp::lib_init();
      iot_client = new mqtt_client("fork_mqtt_shawn_test", "192.168.0.127", 1883);
      // iot_client = new mqtt_client("fork_mqtt_shawn_test", "192.168.0.151", 1883);

      iot_client->subscribe(NULL, "/test");
      iot_client->subscribe(NULL, "/request_fork_control");
      iot_client->subscribe(NULL, "/tray/respose/arrive/at/00");
      iot_client->subscribe(NULL, "/number_of_goods");
      iot_client->subscribe(NULL, "/tray/request/upload/goods");
      timer_1hz_ = nh_.createTimer(ros::Duration(1), &ForkMqtt::timer_1hz_callback, this);
      rc = iot_client->loop();
    }

    void ForkMqtt::autoModeCallback(const cyber_msgs::body_status_feedback &msg)
    {
      is_auto = int(msg.is_auto_drive);
    }

    void ForkMqtt::stagerModeCallback(const std_msgs::Int8 &msg)
    {
      stager_mode_ = msg.data;
    }

    void ForkMqtt::uploadTaskCompleteCallback(const std_msgs::BoolConstPtr &msg)
    {
      if (msg->data == true)
      {
        Json::Value json_object;
        json_object["vehicle"] = "5003";
        json_object["upload_task_done"] = "1";
        iot_client->publish_data("/001/upload_goods_complete/0001/0001/0001/01/0001", json_object);
        // iot_client->publish_data( "/request/goods/number",json_object);
        // iot_client->publish_data( "/request/delete/goods/number",json_object);
      }
    }

    void ForkMqtt::timer_1hz_callback(const ros::TimerEvent &)
    {
      std_msgs::Int8 mqtt_cmd_data_;
      // 从mqtt读取数据 发布到ros
      if (iot_client->getLatestCmdData() != "0")
      {
        mqtt_cmd_data_.data = std::stoi(iot_client->getLatestCmdData());
        pub_cmd_from_mqtt.publish(mqtt_cmd_data_);
        iot_client->resetCmdData();
      }
      // 从mqtt读取数据 发布到ros
      if (iot_client->getPositions() != "")
      {
        std::string positions_string = iot_client->getPositions();
        Json::Reader reader_position;
        Json::Value value_position;
        reader_position.parse(positions_string, value_position);
        std_msgs::Int8MultiArray data_;
        for (uint i = 0; i < value_position.size(); i++)
        {
          data_.data.push_back(stoi(value_position[i].asString()));
        }
        pub_work_positions_.publish(data_);
        std::cout << value_position.size() << std::endl;
        iot_client->resetPositionData();
      }

      // 从mqtt读取数据 发布到ros
      if (iot_client->getUnforkPositions() != "")
      {
        std::string unfork_positions_string = iot_client->getUnforkPositions();
        Json::Reader reader_position;
        Json::Value value_unfork_position;
        reader_position.parse(unfork_positions_string, value_unfork_position);
        std_msgs::Int8MultiArray data1_;
        for (uint i = 0; i < value_unfork_position.size(); i++)
        {
          data1_.data.push_back(stoi(value_unfork_position[i].asString()) + 100);
        }
        pub_work_positions_.publish(data1_);
        iot_client->resetUnforkPositionData();
      }

      if (iot_client->getUploadTast() == true)
      {
        // std_msgs::Int8 upload_task_status;
        // upload_task_status.data = iot_client->get_need_load_position();
        // pub_upload_task_.publish(upload_task_status);
        std_msgs::Bool upload_task_status;
        upload_task_status.data = true;
        pub_upload_task_.publish(upload_task_status);
        iot_client->resetUploadTast();
        iot_client->reset_need_load_position();
      }

      if (iot_client->get_need_fork_position() != -1)
      {
        std_msgs::Int8MultiArray data1_;
        int position = iot_client->get_need_fork_position();
        data1_.data.push_back(position + 50);

        pub_work_positions_.publish(data1_);
        iot_client->reset_need_fork_position();
      }

      // pub_work_unfork_positions_

      // 处理 mqtt 断线重连
      if (rc)
      {
        iot_client->reconnect();
      }
      else
      {
        // 定时发送心跳信号到mqtt broker
        Json::Value json_object;
        count++;
        json_object["count"] = count;
        json_object["vehicle"] = "5003";
        json_object["online"] = "1";
        json_object["stager_mode"] = stager_mode_;
        json_object["is_auto"] = is_auto;
        iot_client->publish_data("/heart/5003", json_object);
      }
    }

    ForkMqtt::~ForkMqtt()
    {
      Json::Value json_object;
      count++;
      json_object["count"] = count;
      json_object["vehicle"] = "5003";
      json_object["online"] = "0";
      iot_client->publish_data("/heart/5003", json_object);
      mosqpp::lib_cleanup();
    }

  } // namespace mqtt
} // namespace cyberc3