# include "socketcan_api.h"

cyberc3::can::CanSocket::CanSocket(const std::string& interfaceName){
	m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (m_socket < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	// 指定can接口
	struct ifreq ifr;
	std::strcpy(ifr.ifr_name, interfaceName.c_str());
	if (ioctl(m_socket, SIOCGIFINDEX, &ifr) < 0) {
		perror("SIOCGIFINDEX");
		exit(EXIT_FAILURE);
	}
	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	// 设定接收CAN报文的ID
	// 设置CAN总线过滤器
    filter[0].can_id = 0x123;
    filter[0].can_mask = CAN_SFF_MASK;
    setsockopt(m_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(filter));
}

bool cyberc3::can::CanSocket::read(can_frame& canFrame) {
        int nbytes = recv(m_socket, &canFrame, sizeof(canFrame), 0);
        if (nbytes < 0) {
            perror("read");
            return false;
        } else if (nbytes < sizeof(can_frame)) {
            std::cerr << "read: incomplete CAN frame" << std::endl;
            return false;
        }

        return true;
    }

bool cyberc3::can::CanSocket::send(const can_frame& canFrame) {
    int nbytes = write(m_socket, &canFrame, sizeof(canFrame));
    if (nbytes < 0) {
        perror("write");
        return false;
    } else if (nbytes < sizeof(can_frame)) {
        std::cerr << "write: incomplete CAN frame" << std::endl;
        return false;
    }
    return true;
}
