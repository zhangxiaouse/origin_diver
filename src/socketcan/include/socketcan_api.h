#pragma once
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>

// #include "cyber_msgs/CanFrame.h"

namespace cyberc3{
	namespace can{
		class CanSocket{
			public:

				CanSocket(const std::string& interfaceName);
				~CanSocket(){};
				bool read(can_frame& canFrame) ;
				bool send(const can_frame& canFrame);
				



			private:
				int m_socket;
				struct can_filter filter[1];
		};
	}
}