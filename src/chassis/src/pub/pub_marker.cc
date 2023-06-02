#include "pub_marker.h"

namespace cyberc3 {
namespace pub {

MarkerPub::MarkerPub(const ros::NodeHandle &nh, const std::string &topic_name,
                     int buff_size)
    : nh_(nh) {
  publisher_ = nh_.advertise<visualization_msgs::Marker>(topic_name, buff_size);
}

void MarkerPub::Publish(double speed_feedback, double time) {
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.orientation.w = 1.0;
  marker.id = 0;
  marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  marker.scale.z = 0.2;
  marker.color.b = 0;
  marker.color.g = 1.0f;
  marker.color.r = 0;
  marker.color.a = 1;
  marker.text = "speed:";
  geometry_msgs::Pose pose;
  marker.id = 0;
  pose.position.x = (float)(0) / 10;
  pose.position.y = 0;
  pose.position.z = 2;
  marker.pose = pose;
  publisher_.publish(marker);
}

} // namespace pub

} // namespace cyberc3
