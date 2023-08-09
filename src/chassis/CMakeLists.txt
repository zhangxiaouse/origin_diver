cmake_minimum_required(VERSION 3.5)
project(chassis)
add_definitions(-std=c++17)
find_package(catkin REQUIRED
             COMPONENTS roscpp
                        rospy
                        std_msgs
                        cyber_msgs
                        geometry_msgs
  )
catkin_package()
include_directories(${catkin_INCLUDE_DIRS}
                    ${GLOG_INCLUDE_DIRS}
                    ${OMPL_INCLUDE_DIRS}
                    ${GFLAGS_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIR}
                    src/
                    ${CMAKE_SOURCE_DIR}
  )
set(SRCS src/tracer/tracer.cc src/lcan/lcan.cc src/pub/pub_array.cc)

set(COMMON_LIBRARIES ${catkin_LIBRARIES} libCanCmd.so)

add_executable(tracer ${SRCS} src/tracer_can_driver_node.cpp)
# Specify libraries to link a library or executable target against
add_dependencies(tracer ${catkin_EXPORTED_TARGETS})
target_link_libraries(tracer ${COMMON_LIBRARIES})

install(TARGETS tracer
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )
install(DIRECTORY launch/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  )
