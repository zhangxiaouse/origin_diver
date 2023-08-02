#ifndef _LCAN_COMMON_H
#define _LCAN_COMMON_H

#include <iostream>
#include <string>

// #include "ros/ros.h"
// #include "std_msgs/Bool.h"
// #include "std_msgs/Float64.h"
// #include "std_msgs/Float64MultiArray.h"
// #include "std_msgs/Int32.h"
// #include "std_msgs/Int32MultiArray.h"
// #include "std_msgs/Int8.h"
// #include "std_msgs/Int8MultiArray.h"
// #include "std_msgs/String.h"

//----------can frame--------------------
// #include "cyber_msgs/ButtonState.h"
// #include "cyber_msgs/CanFrame.h"
// #include "cyber_msgs/SignalState.h"
// #include "sensor_msgs/NavSatFix.h"

//----------can--------------------
#include <fcntl.h>
#include <mutex>
#include <pthread.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "ICANCmd.h"

//-----------------------------------------------------------

using namespace std;

#endif
