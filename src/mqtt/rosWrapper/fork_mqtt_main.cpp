#include "../forkmqtt/forkmqtt.h"
#include "fork_mqtt.h"

int main(int argc, char* argv[]) {
  ros::init(argc, argv, "connect_fork_mqtt");
  ros::NodeHandle nodeHandle("~");
  auto            fork_mqtt_ptr_ = std::make_shared<cyberc3::mqtt::ForkMqtt>(nodeHandle);
  ros::spin();
  mosqpp::lib_cleanup();
  return 0;
}
