/**
 * @ Author: Tong Yao
 * @ Create Time: 2022-11-03 10:06:53
 * @ Modified by: Tong Yao
 * @ Modified time: 2022-11-08 16:58:25
 * @ Description: agv communication by rs232.
 */
#include "crcLib/crcLib.h"

// #include "cyber_msgs/SpeedFeedback.h"
#include "cyber_msgs/LocalizationEstimate.h"
#include "cyber_msgs/SpeedFeedbackAGV.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include "ros/time.h"
#include "sensor_msgs/Imu.h"
#include "serial/serial.h"
#include "tf/transform_datatypes.h"

#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

ros::Publisher pubSpeed;
ros::Publisher pubImu;

bool hz20_;

std::string speed_topic = "/speed_feedback";
std::string imu_topic = "/imu_virtual";
std::string localization_topic = "/localization/estimation_odom";
double wheel_distance = 0.64;

class SerialPort {
public:
  SerialPort(const std::string &port, int baudrate)
      : port_(port), baudrate_(baudrate) {
    ser_.setPort(port_);
    ser_.setBaudrate(baudrate_);
    ser_.setTimeout(to_);
  }
  ~SerialPort() { ser_.close(); }

  bool open() {
    try {
      ser_.open();
    } catch (serial::IOException &e) {
      ROS_ERROR("Unable to open %s!", port_.c_str());
      return false;
    }
    if (ser_.isOpen()) {
      ROS_INFO("%s is opened.", port_.c_str());
      return true;
    } else {
      return false;
    }
  }

  bool isOpen() const { return ser_.isOpen(); }

  void read(std::vector<unsigned char> &buffer) {
    auto num = ser_.available();
    std::vector<unsigned char> recv_data(num);
    ser_.read(recv_data.data(), num);
    buffer.insert(buffer.end(), recv_data.begin(), recv_data.end());
  }

  void write(const std::vector<unsigned char> &buffer) {
    ser_.write(buffer.data(), buffer.size());
  }

private:
  serial::Serial ser_;
  std::string port_;
  int baudrate_;
  serial::Timeout to_ = serial::Timeout::simpleTimeout(20);
};

std::shared_ptr<SerialPort> serial_ptr_;

struct Datapub {
  u_char head;
  uint16_t localization_num;
  int32_t x_mm;
  int32_t y_mm;
  int16_t yaw_mm;
  u_char localization_truth;
  u_char command_info;

  bool isNew;
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

void write_le(unsigned char *buf, int offset, uint64_t value, int size) {
  for (int i = 0; i < size; i++) {
    buf[offset + i] = value & 0xFF;
    value >>= 8;
  }
}

void write_be(unsigned char *buf, int offset, uint64_t value, int size) {
  for (int i = size - 1; i >= 0; i--) {
    buf[offset + i] = value & 0xFF;
    value >>= 8;
  }
}

void send_to_senddata(const Datapub &dataPub,
                      std::vector<unsigned char> &buff) {
  unsigned char send_localization_data[20] = {0};

  write_be(send_localization_data, 0, dataPub.head, 1);
  write_be(send_localization_data, 1, dataPub.localization_num, 2);
  write_be(send_localization_data, 3, dataPub.x_mm, 4);
  write_be(send_localization_data, 7, dataPub.y_mm, 4);
  write_be(send_localization_data, 11, dataPub.yaw_mm, 2);
  write_be(send_localization_data, 13, dataPub.localization_truth, 1);
  write_be(send_localization_data, 14, dataPub.command_info, 1);
  uint16_t temp_16 = crc16(send_localization_data, 18);
  write_be(send_localization_data, 18, temp_16, 2);

  std::vector<unsigned char> send_localization_vector(
      send_localization_data, send_localization_data + 20);
  buff = std::move(send_localization_vector);
}

void localizationCallback(const nav_msgs::OdometryConstPtr &msg) {
  auto x = msg->pose.pose.position.x;
  auto y = msg->pose.pose.position.y;

  tf::Quaternion quat;
  double roll, pitch, yaw;
  tf::quaternionMsgToTF(msg->pose.pose.orientation, quat);
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

  static int localization_count = 0;
  localization_count++;

  dataPub.head = 0x41;
  dataPub.localization_num = localization_count;
  dataPub.x_mm = int(x * 1000);
  dataPub.y_mm = int(y * 1000);
  dataPub.yaw_mm = float(yaw / (2 * M_PI) * 360 * 10);
  dataPub.localization_truth = 1;
  dataPub.command_info = 1;

  dataPub.isNew = true;
}

void reveive() {
  std::vector<unsigned char> read_buffer;
  const int TARGET_LENGTH = 20;
  const unsigned char TARGET_HEADER = 0x41;
  while (ros::ok()) {
    serial_ptr_->read(read_buffer);
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
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

// void speed_data_tomsg(){
//     speed_data_msg.header.stamp = ros::T               ros::ok() ime::now();
//     speed_data_msg.speed_cmps = (dataSub.speed_left +
//     dataSub.speed_right)
//     * 0.1 * 0.5; speed_data_msg.speed_kmph = (dataSub.speed_left +
//     dataSub.speed_right) * 0.001 * 0.5 * 3.6;
// }

void send() {
  while (ros::ok()) {
    if (hz20_) {
      static double last_time = ros::Time::now().toSec();
      if (dataPub.isNew == true) {
        last_time = ros::Time::now().toSec();
        std::vector<unsigned char> send_localization_vector;
        send_to_senddata(dataPub, send_localization_vector);
        serial_ptr_->write(send_localization_vector);
        dataPub.isNew = false;
      }
      if (ros::Time::now().toSec() - last_time >= 0.05) {
        ROS_WARN("Localization data lost about : %lfs.",
                 ros::Time::now().toSec() - last_time);
      }

      cyber_msgs::SpeedFeedbackAGV speed_data_msg;
      speed_data_msg.header.stamp = ros::Time::now();
      speed_data_msg.speed_left_cmps = dataSub.speed_left * 0.1;
      speed_data_msg.speed_right_cmps = dataSub.speed_right * 0.1;
      pubSpeed.publish(speed_data_msg);
      std::cout << " publish ros data [" << dataSub.speed_left << ", "
                << dataSub.speed_right << "] " << std::endl;

      sensor_msgs::Imu imu_data_msg;
      imu_data_msg.header.stamp = ros::Time::now();
      imu_data_msg.header.frame_id = "base_link";
      imu_data_msg.angular_velocity.z =
          (dataSub.speed_right - dataSub.speed_left) * 0.001 / wheel_distance;
      pubImu.publish(imu_data_msg);

      hz20_ = false;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
}

void timer() {
  while (ros::ok()) {
    static int count = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (count % 5 == 0) {
      hz20_ = true;
    }
    count++;
  }
}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "serial_pub_sub");
  ros::NodeHandle n("~");

  std::string serial_port = "/dev/ttyUSB0";
  int baudrate = 115200;
  n.param("serial_port", serial_port, serial_port);
  n.param("baudrate", baudrate, baudrate);
  n.param("speed_topic", speed_topic, speed_topic);
  n.param("imu_topic", imu_topic, imu_topic);
  n.param("localization_topic", localization_topic, localization_topic);
  n.param("wheel_distance", wheel_distance, wheel_distance);

  std::cout << serial_port << std::endl;

  pubSpeed = n.advertise<cyber_msgs::SpeedFeedbackAGV>(speed_topic, 100);
  pubImu = n.advertise<sensor_msgs::Imu>(imu_topic, 100);
  auto sublocalization =
      n.subscribe(localization_topic, 1, localizationCallback);

  serial_ptr_ = std::make_shared<SerialPort>(serial_port, baudrate);
  if (!serial_ptr_->open()) {
    return -1;
  }

  std::thread receive_thread(&reveive);
  std::thread timer_thread(&timer);
  std::thread send_thread(&send);

  ros::spin();

  return 0;
}