find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  cyber_msgs
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})
link_libraries(${catkin_LIBRARIES})


add_executable(fork_mqtt_main_node fork_mqtt_main.cpp fork_mqtt.cc)
target_link_libraries(fork_mqtt_main_node
  ${PROJECT_NAME}_forkmqtt
)