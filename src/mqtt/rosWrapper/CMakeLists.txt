find_package(catkin REQUIRED
             COMPONENTS roscpp
                        rospy
                        std_msgs
                        geometry_msgs
                        cyber_msgs
  )

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})
link_libraries(${catkin_LIBRARIES})

add_executable(fork_mqtt_main_node fork_mqtt.cc fork_mqtt_main.cpp)

target_link_libraries(fork_mqtt_main_node ${PROJECT_NAME}_forkmqtt)

install(TARGETS fork_mqtt_main_node
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )
install(DIRECTORY launch/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  )
