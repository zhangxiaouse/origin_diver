/**
 * @ Author: Tong Yao
 * @ Create Time: 2022-11-03 10:06:53
 * @ Modified by: Tong Yao
 * @ Modified time: 2022-11-08 16:58:25
 * @ Description: agv communication by rs232.
 */
#include "crcLib/crcLib.h"
#include "cyber_msgs/LocalizationEstimate.h"
// #include "cyber_msgs/SpeedFeedback.h"
#include "cyber_msgs/SpeedFeedbackAGV.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include "ros/time.h"
#include "sensor_msgs/Imu.h"
#include "serial/serial.h"
#include "tf/transform_datatypes.h"

#include <iostream>

serial::Serial ser;
serial::Timeout to = serial::Timeout::simpleTimeout(serial::Timeout::max());

std::string serial_port = "/dev/ttyUSB0";
int baudrate = 115200;
std::string speed_topic = "/speed_feedback";
std::string imu_topic = "/imu_virtual";
std::string localization_topic = "/localization/estimation_odom";
double wheel_distance = 0.64;

unsigned char send_localization_data[20] = {0};

int localization_count = 0;

struct Datapub {
  u_char head;
  uint16_t localization_num;
  int32_t x_mm;
  int32_t y_mm;
  int16_t yaw_mm;
  u_char localization_truth;
  u_char command_info;
};
Datapub dataPub;

struct Datasub {
  u_char head;
  uint16_t localization_num;
  int32_t speed_left;
  int32_t speed_right;
  uint32_t timestamp;
};
Datasub dataSub;

void send_to_senddata(const Datapub &dataPub) {

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

  temp_16 = crc16(send_localization_data, 18);
  for (int i = 19; i > 17; i--) {
    send_localization_data[i] = 0;
    send_localization_data[i] |= temp_16;
    temp_16 >>= 8;
  }
}

void localizationCallback(const nav_msgs::OdometryConstPtr &msg) {
  static double last_time = ros::Time::now().toSec();
  if (ros::Time::now().toSec() - last_time >= 0.05) {
    // ROS_INFO("Callback time: %lf.", ros::Time::now().toSec());
    last_time = ros::Time::now().toSec();
    auto x = msg->pose.pose.position.x;
    auto y = msg->pose.pose.position.y;

    // 3D -> 2D
    tf::Quaternion quat;
    double roll, pitch, yaw;
    tf::quaternionMsgToTF(msg->pose.pose.orientation, quat);
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    localization_count++;

    dataPub.head = 0x41;
    dataPub.localization_num = localization_count;
    dataPub.x_mm = int(x * 1000);
    dataPub.y_mm = int(y * 1000);
    dataPub.yaw_mm = float(yaw / (2 * M_PI) * 360 * 10);
    dataPub.localization_truth = 1;
    dataPub.command_info = 1;

    send_to_senddata(dataPub);

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

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "serial_pub_sub");
  ros::NodeHandle n("~");

  n.param("serial_port", serial_port, serial_port);
  n.param("baudrate", baudrate, baudrate);
  n.param("speed_topic", speed_topic, speed_topic);
  n.param("imu_topic", imu_topic, imu_topic);
  n.param("localization_topic", localization_topic, localization_topic);
  n.param("wheel_distance", wheel_distance, wheel_distance);

  std::cout << serial_port << std::endl;

  // n.advertise<cyber_msgs::SpeedFeedback>(speed_topic, 1000);
  auto pubSpeed = n.advertise<cyber_msgs::SpeedFeedbackAGV>(speed_topic, 100);
  auto pubImu = n.advertise<sensor_msgs::Imu>(imu_topic, 100);
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

  ros::Rate loop_rate(20);
  std::vector<unsigned char> read_buffer;
  while (ros::ok()) {
    ros::spinOnce();

    const int TARGET_LENGTH = 20;
    const unsigned char TARGET_HEADER = 0x41;

    if (auto num = ser.available()) {
      std::vector<unsigned char> recv_data(num);

      ser.read(recv_data.data(), num);
      read_buffer.insert(read_buffer.end(), recv_data.begin(), recv_data.end());

      while (read_buffer.size() >= TARGET_LENGTH) {
        if (read_buffer.front() != TARGET_HEADER) {
          read_buffer.erase(read_buffer.begin());
          continue;
        }
        if (read_buffer.size() >= TARGET_LENGTH) {
          std::vector<unsigned char> parse_speed_data(TARGET_LENGTH);
          std::move(read_buffer.begin(), read_buffer.begin() + TARGET_LENGTH,
                    parse_speed_data.begin());
          read_buffer.erase(read_buffer.begin(),
                            read_buffer.begin() + TARGET_LENGTH);

          // 处理提取出来的数据
          // ROS_INFO("Begin decoding...");
          if (((parse_speed_data[18] << 8) | parse_speed_data[19]) ==
              crc16(parse_speed_data.data(), 18)) {
            dataSub.localization_num =
                (uint16_t)((parse_speed_data[1] << 8) | parse_speed_data[2]);
            dataSub.speed_left =
                (int32_t)((parse_speed_data[3] << 24) |
                          (parse_speed_data[4] << 16) |
                          (parse_speed_data[5] << 8) | parse_speed_data[6]);
            dataSub.speed_right =
                (int32_t)((parse_speed_data[7] << 24) |
                          (parse_speed_data[8] << 16) |
                          (parse_speed_data[9] << 8) | parse_speed_data[10]);
            dataSub.timestamp =
                (int32_t)((parse_speed_data[11] << 24) |
                          (parse_speed_data[12] << 16) |
                          (parse_speed_data[13] << 8) | parse_speed_data[14]);
          } else {
            ROS_WARN("Invalid Data, Something went wrong...");
          }
        }
      }
    }
    cyber_msgs::SpeedFeedbackAGV speed_data_msg;
    speed_data_msg.header.stamp = ros::Time::now();
    speed_data_msg.speed_left_cmps = dataSub.speed_left * 0.1;
    speed_data_msg.speed_right_cmps = dataSub.speed_right * 0.1;
    pubSpeed.publish(speed_data_msg);

    sensor_msgs::Imu imu_data_msg;
    imu_data_msg.header.stamp = ros::Time::now();
    imu_data_msg.header.frame_id = "base_link";
    imu_data_msg.angular_velocity.z =
        (dataSub.speed_right - dataSub.speed_left) * 0.001 / wheel_distance;
    pubImu.publish(imu_data_msg);

    loop_rate.sleep();
  }

  return 0;
}
