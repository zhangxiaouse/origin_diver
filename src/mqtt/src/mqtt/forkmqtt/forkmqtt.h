#ifndef SIMPLECLIENT_MQTT_H
#define SIMPLECLIENT_MQTT_H
#include <jsoncpp/json/json.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <mosquittopp.h>
#include <mutex>
#define MAX_PAYLOAD 200
#define DEFAULT_KEEP_ALIVE 60

namespace cyberc3
{
  namespace mqtt
  {

    class mqtt_client : public mosqpp::mosquittopp
    {

    private:
      int need_load_position = -1;
      int need_fork_position = -1;
      int cmd_from_ = -1;
      int cmd_to_ = -1;
      // 叉车所需要叉取的货物位置
      std::string cmd_ = "0";
      std::string positions_ = "";
      std::string unfork_positions_ = "";

      bool upload_task_ = false;
      std::mutex publish_lock_;

      int number_of_goods = 1;
      // TODO 如何防止第一次无法启动
    public:
      mqtt_client(const char *id, const char *host, int port);
      ~mqtt_client();

      void on_connect(int rc);
      void on_message(const struct mosquitto_message *message);
      void on_subscribe(int mid, int qos_count, const int *granted_qos);
      void publish_data(const std::string &topic_name, const Json::Value &jsondata);
      std::string getLatestCmdData()
      {
        return cmd_;
      }
      std::string getPositions()
      {
        return positions_;
      }
      std::string getUnforkPositions()
      {
        return unfork_positions_;
      }
      bool resetCmdData()
      {
        cmd_ = "0";
        return true;
      }
      bool resetPositionData()
      {
        positions_ = "";
        return true;
      }
      bool resetUnforkPositionData()
      {
        unfork_positions_ = "";
        return true;
      }
      bool getUploadTast()
      {
        return upload_task_;
      }
      bool resetUploadTast()
      {
        upload_task_ = false;
        return true;
      }

      int get_from_()
      {
        return cmd_from_;
      }
      int reset_from_()
      {
        cmd_from_ = -1;
      }

      int get_to_()
      {
        return cmd_to_;
      }
      int reset_to_()
      {
        cmd_to_ = -1;
      }

      int get_need_load_position()
      {
        return need_load_position;
      }
      int reset_need_load_position()
      {
        need_load_position = -1;
        return true;
      }

      int get_need_fork_position()
      {
        return need_fork_position;
      }
      int reset_need_fork_position()
      {
        need_fork_position = -1;
        return true;
      }
    };

  } // namespace mqtt
} // namespace cyberc3

#endif // SIMPLECLIENT_MQTT_H