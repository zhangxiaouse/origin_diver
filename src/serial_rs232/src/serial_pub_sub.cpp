/**
 * @ Author: Tong Yao
 * @ Create Time: 2022-11-03 10:06:53
 * @ Modified by: Tong Yao
 * @ Modified time: 2022-11-08 16:58:25
 * @ Description: agv communication by rs232.
 */
#include "crcLib/crcLib.h"
#include "cyber_msgs/LocalizationEstimate.h"
#include "cyber_msgs/SpeedFeedback.h"
#include "cyber_msgs/SpeedFeedbackAGV.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include "ros/time.h"
#include "sensor_msgs/Imu.h"
#include "serial/serial.h"
#include "tf/transform_datatypes.h"

#include <iostream>

serial::Serial ser;
// serial::Timeout to = serial::Timeout::simpleTimeout(20);
serial::Timeout to = serial::Timeout::simpleTimeout(serial::Timeout::max());

std::string serial_port = "/dev/ttyS0";
int baudrate = 115200;
std::string speed_topic = "/speed_feedback";
std::string imu_topic = "/imu_virtual";
std::string localization_topic = "/localization/estimation_odom";
double wheel_distance = 0.64;

unsigned char send_localization_data[20] = {0};
unsigned char recv_speed_data[20] = {0};

double now_time = 0.0;

int filter = 0;

// define pub localization
struct Datapub {
  u_char head;
  uint16_t localization_num;
  int32_t x_mm;
  int32_t y_mm;
  int16_t yaw_mm;
  u_char localization_truth;
  u_char command_info;

  uint16_t crc_16;
};

double x = 0.0;
double y = 0.0;
double yaw = 0.0;
int localization_count = 0;
Datapub dataPub;

// define sub speed
// cyber_msgs::SpeedFeedback speed_data_msg;
cyber_msgs::SpeedFeedbackAGV speed_data_msg;
sensor_msgs::Imu imu_data_msg;

struct Datasub {
  u_char head;
  uint16_t localization_num;
  int32_t speed_left;  // mm/s
  int32_t speed_right; // mm/s
  uint32_t timestamp;

  uint16_t crc_16;
};

Datasub dataSub;
int compute_crc_sub;

void send_to_senddata() {

  send_localization_data[0] = dataPub.head;
  uint16_t temp_16 = dataPub.localization_num;
  for (int i = 2; i > 0; i--) {
    send_localization_data[i] = 0;
    send_localization_data[i] |= temp_16;
    temp_16 >>= 8;
  }
  uint32_t temp_32 = dataPub.x_mm;
  for (int i = 6; i > 2; i--) {
    send_localization_data[i] = 0;
    send_localization_data[i] |= temp_32;
    temp_32 >>= 8;
  }
  temp_32 = dataPub.y_mm;
  for (int i = 10; i > 6; i--) {
    send_localization_data[i] = 0;
    send_localization_data[i] |= temp_32;
    temp_32 >>= 8;
  }
  temp_16 = dataPub.yaw_mm;
  for (int i = 12; i > 10; i--) {
    send_localization_data[i] = 0;
    send_localization_data[i] |= temp_16;
    temp_16 >>= 8;
  }
  send_localization_data[13] = dataPub.localization_truth;
  send_localization_data[14] = dataPub.command_info;

  dataPub.crc_16 = crc16(send_localization_data, 18);
  temp_16 = dataPub.crc_16;
  for (int i = 19; i > 17; i--) {
    send_localization_data[i] = 0;
    send_localization_data[i] |= temp_16;
    temp_16 >>= 8;
  }
}

void localizationCallback(const nav_msgs::OdometryConstPtr &msg) {

  // filter++;

  if (ros::Time::now().toSec() - now_time >= 0.05) {
    // ROS_INFO("Callback time: %lf.", ros::Time::now().toSec());
    now_time = ros::Time::now().toSec();
    x = msg->pose.pose.position.x;
    y = msg->pose.pose.position.y;

    // 3D -> 2D
    tf::Quaternion quat;
    double roll, pitch, yaw;
    quat.setX(msg->pose.pose.orientation.x);
    quat.setY(msg->pose.pose.orientation.y);
    quat.setZ(msg->pose.pose.orientation.z);
    quat.setW(msg->pose.pose.orientation.w);
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    localization_count++;

    dataPub.head = 0x41;
    dataPub.localization_num = localization_count;
    dataPub.x_mm = int(x * 1000);
    dataPub.y_mm = int(y * 1000);
    dataPub.yaw_mm = float(yaw / (2 * M_PI) * 360 * 10);
    dataPub.localization_truth = 1;
    dataPub.command_info = 1;

    dataPub.crc_16 = 0;

    send_to_senddata();

    ser.write(send_localization_data, 20);
    send_localization_data[20] = {0};

    // ROS_INFO("Localization data timestamp: %lf.", msg->header.stamp.toSec());
    ROS_INFO("Write localization data num %u to %s.", localization_count,
             serial_port.c_str());
  }
}

// void speed_data_tomsg(){

//     speed_data_msg.header.stamp = ros::Time::now();

//     speed_data_msg.speed_cmps = (dataSub.speed_left + dataSub.speed_right) *
//     0.1 * 0.5; speed_data_msg.speed_kmph = (dataSub.speed_left +
//     dataSub.speed_right) * 0.001 * 0.5 * 3.6;

// }

void speed_data_tomsg() {

  speed_data_msg.header.stamp = ros::Time::now();

  speed_data_msg.speed_left_cmps = dataSub.speed_left * 0.1;
  speed_data_msg.speed_right_cmps = dataSub.speed_right * 0.1;
}

void imu_data_tomsg() {

  imu_data_msg.header.stamp = ros::Time::now();
  imu_data_msg.angular_velocity.z =
      (dataSub.speed_right - dataSub.speed_left) * 0.001 /
      wheel_distance; // 0.64 = distance of two wheels
}

void speed_data_handle(ros::Publisher pubSpeed, ros::Publisher pubImu) {
  //  begin decoding datas
  ROS_INFO("Begin decoding...");

  if (recv_speed_data[0] == 0x41 &&
      ((recv_speed_data[18] << 8) | recv_speed_data[19]) ==
          crc16(recv_speed_data, 18)) {

    uint16_t temp_16_s = (recv_speed_data[1] << 8) | (recv_speed_data[2]);
    dataSub.localization_num = temp_16_s;
    uint32_t temp_32_s = (recv_speed_data[3] << 24) |
                         (recv_speed_data[4] << 16) |
                         (recv_speed_data[5] << 8) | (recv_speed_data[6]);
    dataSub.speed_left = int(temp_32_s);
    temp_32_s = (recv_speed_data[7] << 24) | (recv_speed_data[8] << 16) |
                (recv_speed_data[9] << 8) | (recv_speed_data[10]);
    dataSub.speed_right = int(temp_32_s);
    temp_32_s = (recv_speed_data[11] << 24) | (recv_speed_data[12] << 16) |
                (recv_speed_data[13] << 8) | (recv_speed_data[14]);
    dataSub.timestamp = int(temp_32_s);
    ROS_INFO("Read data num %u.", dataSub.localization_num);
    if (abs(dataSub.localization_num - localization_count) > 5) {
      ROS_WARN("Communication delay beyond 0.05s!");
    }
    speed_data_tomsg();
    imu_data_tomsg();
    pubSpeed.publish(speed_data_msg);
    pubImu.publish(imu_data_msg);
  } else {
    ROS_WARN("InValid Data, Something got wrong... ");
  }
}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "serial_pub_sub");
  ros::NodeHandle n("~");

  // double now_time = ros::Time::now().toSec();

  n.param("serial_port", serial_port, serial_port);
  n.param("baudrate", baudrate, baudrate);
  n.param("speed_topic", speed_topic, speed_topic);
  n.param("imu_topic", imu_topic, imu_topic);
  n.param("localization_topic", localization_topic, localization_topic);
  n.param("wheel_distance", wheel_distance, wheel_distance);

  std::cout << serial_port << std::endl;
  std::cout << baudrate << std::endl;
  std::cout << serial_port << std::endl;
  std::cout << serial_port << std::endl;
  std::cout << serial_port << std::endl;

  // ros::Publisher pubSpeed =
  // n.advertise<cyber_msgs::SpeedFeedback>(speed_topic, 1000);
  ros::Publisher pubSpeed =
      n.advertise<cyber_msgs::SpeedFeedbackAGV>(speed_topic, 1000);
  ros::Publisher pubImu = n.advertise<sensor_msgs::Imu>(imu_topic, 1000);
  ros::Subscriber sublocalization =
      n.subscribe(localization_topic, 1, localizationCallback);

  ser.setPort(serial_port);
  ser.setBaudrate(baudrate);
  ser.setTimeout(to);

  try {
    ser.open();
  } catch (serial::IOException &e) {
    ROS_ERROR("Unable to open %s!", serial_port.c_str());
    return -1;
  }

  if (ser.isOpen()) {
    ROS_INFO("%s is opened.", serial_port.c_str());
  } else {
    return -1;
  }

  ros::Rate loop_rate(5000);
  while (ros::ok()) {
    ros::spinOnce();

    if (ser.available()) {
      ser.read(recv_speed_data, 20);
      speed_data_handle(pubSpeed, pubImu);
    }

    loop_rate.sleep();
  }

  // if(ser.available()){
  //     ser.read(recv_speed_data, 20);
  //     speed_data_handle(pubSpeed, pubImu);
  // }

  // ros::spin();

  return 0;
}
