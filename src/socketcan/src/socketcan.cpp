# include "socketcan_api.h"
#include <iostream>
#include <thread>

int main() {
    std::cout << "socket can node start!" << std::endl;
    // 创建CanSocket对象
    cyberc3::can::CanSocket canSocket("can0");

    // 待发送的 CAN 报文
    can_frame canFrame;
    canFrame.can_id = 0x456;  // 设置 CAN ID
    canFrame.can_dlc = 3;     // 设置数据长度
    canFrame.data[0] = 0x11;  // 设置数据内容
    canFrame.data[1] = 0x22;
    canFrame.data[2] = 0x33;

    // 创建发送线程
    std::thread sendThread([&]() {
        while (true) {
            // 发送 CAN 报文
            if (!canSocket.send(canFrame)) {
                std::cerr << "Failed to send CAN frame" << std::endl;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 每隔100ms发送一次
        }
    });

    // 创建接收线程
    std::thread recvThread([&]() {
        while (true) {
            // 读取CAN报文
            can_frame recvFrame;
            if (canSocket.read(recvFrame)) {
                std::cout << "Received CAN frame: ID = " << recvFrame.can_id << ", Data = ";
                for (int i = 0; i < recvFrame.can_dlc; i++) {
                    std::cout << std::hex << (int)recvFrame.data[i] << " ";
                }
                std::cout << std::endl;
            }
        }
    });

    // 等待两个线程结束
    sendThread.join();
    recvThread.join();

    return 0;
}