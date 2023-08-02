#include "forkmqtt.h"
#define PUBLISH_TOPIC "/request_fork_control"
#define UPLOAD_TASK "/tray/respose/arrive/at/00"
// #define NUMBER_OF_GOODS "/number_of_goods"
// #define NUMBER_OF_GOODS "/tray/request/upload/goods"
#define SET_FORK_POSITION "/tray/request/upload/goods"
// 设置叉车叉取货物的位置

// #define DOWNLOAD_GOODS_COMPLETE "/001/download_goods_complete/0001/0001/0001/01/0002"

#include <iostream>
#include <jsoncpp/json/json.h>

namespace cyberc3
{
  namespace mqtt
  {

    mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
    {
      int keepalive = DEFAULT_KEEP_ALIVE;
      connect_async(host, port, keepalive);
      loop_start();
    }

    mqtt_client::~mqtt_client() {}

    void mqtt_client::on_connect(int rc)
    {
      std::cout << "mqtt Connected!" << rc << std::endl;
    }

    void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
    {
      std::cout << "Subscription succeeded." << std::endl;
    }

    void mqtt_client::on_message(const struct mosquitto_message *message)
    {
      int payload_size = MAX_PAYLOAD + 1;
      char buf[payload_size];
      if (!strcmp(message->topic, PUBLISH_TOPIC))
      {
        memset(buf, 0, payload_size * sizeof(char));
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
        Json::Reader reader;
        Json::Reader reader_position;
        Json::Value value;
        Json::Value value_position;
        reader.parse(buf, value);
        cmd_ = value["cmd"].asString();
        // positions_ = value["positions"].asString();
        if (cmd_ == "8")
        {
          positions_ = value["positions"].asString();
        }
        else if (cmd_ == "9")
        {
          unfork_positions_ = value["positions"].asString();
        }
        reader_position.parse(positions_, value_position);
        // std::cout<<value_position.size()<<std::endl;
        // std::cout<<stoi(value_position[0].asString())<<std::endl;
      }
      else if (!strcmp(message->topic, UPLOAD_TASK))
      {
        upload_task_ = true;
        memset(buf, 0, payload_size * sizeof(char));
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
        Json::Reader reader;
        Json::Reader reader_position;
        Json::Value value;
        Json::Value value_position;
        reader.parse(buf, value);
        need_load_position = value["work_station"].asInt();
      }
      else if (!strcmp(message->topic, SET_FORK_POSITION))
      {
        std::cout << message->topic << std::endl;
        memset(buf, 0, payload_size * sizeof(char));
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
        Json::Reader reader;
        Json::Reader reader_position;
        Json::Value value;
        Json::Value value_position;
        reader.parse(buf, value);
        need_fork_position = value["station"].asInt();
      }
      else if (!strcmp(message->topic, "/test"))
      {
        std::cout << message->topic << std::endl;
        memset(buf, 0, payload_size * sizeof(char));
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
        Json::Reader reader;
        Json::Value value;
        reader.parse(buf, value);
        cmd_from_ = value["from_"].asInt();
        cmd_to_ = value["to_"].asInt();
      }
      else if (!strcmp(message->topic, "/web/publish/cmd"))
      {
        std::cout << message->topic << std::endl;
        memset(buf, 0, payload_size * sizeof(char));
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
        Json::Reader reader;
        Json::Value value;
        reader.parse(buf, value);
        web_cmd_ = value["cmd_"].asInt();
        std::cout << web_cmd_ << std::endl;
        web_cmd_value_ = value["value_"].asInt();
        std::cout << web_cmd_value_ << std::endl;
      }
      else if (!strcmp(message->topic, "/0001/web/publish/dispatch/"))
      {
        std::cout << message->topic << std::endl;
        memset(buf, 0, payload_size * sizeof(char));
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
        Json::Reader reader;
        Json::Value value;
        reader.parse(buf, value);
        selectedLine_ = value["selectedLine_"].asString();
        selectedVehicle_ = value["selectedVehicle_"].asString();
        std::cout << selectedLine_ << std::endl;
        std::cout << selectedVehicle_ << std::endl;
        selectedStation_ = value["selectedStation_"].asInt();
        std::cout << selectedStation_ << std::endl;
      }
      // else if(!strcmp(message->topic, SET_FORK_POSITION))
      //   {
      //     std::cout<<message->topic<<std::endl;
      //     memset(buf, 0, payload_size * sizeof(char));
      //     memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
      //     Json::Reader reader;
      //     Json::Reader reader_position;
      //     Json::Value value;
      //     Json::Value value_position;
      //     reader.parse(buf,value);
      //     number_of_goods = value["numbers"].asInt();
      // }
    }

    void mqtt_client::publish_data(const std::string &topic_name, const Json::Value &jsondata)
    {
      std::lock_guard<std::mutex> lock(publish_lock_);
      std::string msg = jsondata.toStyledString();
      int len = msg.length();
      publish(NULL, topic_name.c_str(), len, msg.data(), 1, false);
    }

  } // namespace mqtt
} // namespace cyberc3
