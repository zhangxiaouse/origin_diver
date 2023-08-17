#include "tracer_can_driver_node.h"

namespace cyberc3 {
namespace node {
tracer_can_driver_node::tracer_can_driver_node(const ros::NodeHandle &nh,
                                               const ros::NodeHandle &pnh)
    : nh_(nh), pnh_(pnh) {
  can_bridge_ptr_.reset(new cyber_c3::can_bridge::lcan(false));
  tracer_ptr_ = std::make_shared<cyberc3::vehicle::tracer>();
  array_pub_ptr_ =
      std::make_shared<cyberc3::pub::arrayPub>(nh_, "/tracer/can_data", 1);
  publish_vehicle_speed_ =
      nh_.advertise<cyber_msgs::AGVSpeedFeedback>("/tracer/speedback", 1);
  publish_vehicle_speed_4_lidarlocalization =
      nh_.advertise<cyber_msgs::SpeedFeedbackDiff>("/speed_feedback", 1);

  subscriber_agv_speed_ = nh_.subscribe(
      "/agv/speedcmd", 1, &tracer_can_driver_node::speed_msg_callback, this);
  timer_50hz_ = nh_.createTimer(
      ros::Duration(0.02), &tracer_can_driver_node::Timer50hzCallback, this);
  subscriber_web_cmd_ =
      nh_.subscribe("/web/request/auto", 1,
                    &tracer_can_driver_node::web_cmd_msg_callback, this);
subscriber_perception_emergency_ = 
      nh_.subscribe("/perception/emergency", 1,
                    &tracer_can_driver_node::perception_cmd_msg_callback, this);

}
void tracer_can_driver_node::perception_cmd_msg_callback(const std_msgs::Int8 msg) {
      tracer_feedback_ptr_.emergency = msg.data;
}

void tracer_can_driver_node::web_cmd_msg_callback(const std_msgs::Bool msg) {
  if (msg.data == true) {
    is_auto_ = TRUE;
  } else if (msg.data == false) {
    is_auto_ = FALSE;
  }
}

void tracer_can_driver_node::speed_msg_callback(
    const cyber_msgs::AGVSpeedCmd msg) {
  tracer_command_ptr_.left_speed_mps = msg.left_cmd_mps;
  tracer_command_ptr_.right_speed_mps = msg.right_cmd_mps;
}

void tracer_can_driver_node::receive() {
  cyberc3::basic::can thiscan;
  for (size_t i = 0; i < 8; i++) {
    thiscan.data[i] = 0;
  }

  uint16_t can_frame_[10] = {};
  double time_;
  int received_can_frame = 0;
  while (1) {
    usleep(10);  // 0.1ms = 10000hz
    received_can_frame = can_bridge_ptr_->Read(thiscan);
    if (received_can_frame == 0) {
      continue;
    }

    can_frame_[0] = thiscan.id;
    can_frame_[1] = thiscan.len;
    for (size_t i = 2; i < 10; i++) {
      can_frame_[i] = thiscan.data[i - 2];
    }
    time_ = ros::Time::now().nsec;
    array_pub_ptr_->Publish(can_frame_, 10, 1);
    for (auto n : tracer_ptr_->WhiteList) {
      if (n == thiscan.id) {
        tracer_ptr_->Decode(thiscan, ros::Time::now().toSec(),
                            tracer_feedback_ptr_);

        break;
      }
    }
  }
}

void tracer_can_driver_node::Timer50hzCallback(const ros::TimerEvent &) {
  // 将底层车辆的速度发布出去
  v_ = tracer_feedback_ptr_.speed * 0.001;
  r_ = tracer_feedback_ptr_.rotate * 0.001;

  cyber_msgs::AGVSpeedFeedback agv_speed_feedback_;
  agv_speed_feedback_.header.stamp = ros::Time::now();
  agv_speed_feedback_.left_speed_mps = v_ - (r_ * d_) * 0.5;
  agv_speed_feedback_.right_speed_mps = v_ + (r_ * d_) * 0.5;
  publish_vehicle_speed_.publish(agv_speed_feedback_);

  cyber_msgs::SpeedFeedbackDiff speed_feedback_agv_;
  speed_feedback_agv_.header.stamp = ros::Time::now();
  speed_feedback_agv_.speed_left_cmps =
      agv_speed_feedback_.left_speed_mps * 100;
  speed_feedback_agv_.speed_right_cmps =
      agv_speed_feedback_.right_speed_mps * 100;
  speed_feedback_agv_.speed_cmps = tracer_feedback_ptr_.speed * 0.1;
  speed_feedback_agv_.angular_velocity = tracer_feedback_ptr_.rotate * 0.001;
  publish_vehicle_speed_4_lidarlocalization.publish(speed_feedback_agv_);

  // 将上层控制的速度转向指令信息通过can发布出去
  cyberc3::basic::can CanData;
  if (is_auto_ == true) {
    std::cout << "is_auto true" << std::endl;
    tracer_ptr_->setSteerSpeed(tracer_feedback_ptr_, tracer_command_ptr_,
                               CanData);
    can_bridge_ptr_->Write(CanData);
  } else {
    tracer_feedback_ptr_.is_init = false;
  }
}
}  // namespace node
}  // namespace cyberc3

int main(int argc, char **argv) {
  ros::init(argc, argv, "VehicleCanNode");
  ros::NodeHandle nh_;
  ros::NodeHandle pnh_("~");
  cyberc3::node::tracer_can_driver_node tracer_can_driver_node_(nh_, pnh_);
  std::thread receive_thread(&cyberc3::node::tracer_can_driver_node::receive,
                             std::ref(tracer_can_driver_node_));
  ros::spin();
}