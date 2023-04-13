cmake_minimum_required(VERSION 3.0.2)
project(serial_rs232)

add_compile_options(-std=c++17)

find_package(
  catkin REQUIRED
  COMPONENTS roscpp
             rospy
             serial
             geometry_msgs
             nav_msgs
             sensor_msgs
             std_msgs
             cyber_msgs
             tf)

catkin_package(
  CATKIN_DEPENDS
  geometry_msgs
  nav_msgs
  sensor_msgs
  roscpp
  rospy
  serial
  std_msgs
  tf
  DEPENDS
  LIBRARIES)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(serial_pub_sub src/serial_pub_sub.cpp src/crcLib/crcLib.cpp)

target_link_libraries(serial_pub_sub ${catkin_LIBRARIES})
# add_dependencies(localization ${catkin_EXPORTED_TARGETS})

install(
  TARGETS serial_pub_sub
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY launch/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch)
