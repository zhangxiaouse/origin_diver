cmake_minimum_required(VERSION 2.8.0)
project(cyberc3_mqtt)

#######################################################
###  Compiler Options
#######################################################
#set(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_BUILD_TYPE "Build")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

#######################################################
###  Build which Module
#######################################################

#######################################################
###  Dependencies
#######################################################
set(require_third_libs "")
include_directories(".")

list(APPEND require_third_libs mosquittopp)
list(APPEND require_third_libs jsoncpp)

#######################################################
###  Source files
#######################################################
add_subdirectory(forkmqtt)
add_subdirectory(carstate)

#######################################################
###  Display
#######################################################
# set(${PROJECT_NAME}_libs "")
# list(APPEND ${PROJECT_NAME}_libs
#     ${PROJECT_NAME}_TONGYI
#     ${PROJECT_NAME}_canbasic
# )

# message(STATUS "CXX FLAGS: ${CMAKE_CXX_FLAGS}")
# message(STATUS "Third party libs: ${require_third_libs}")
# message(STATUS "Local link  libs: ${${PROJECT_NAME}_libs}")

#######################################################
###  ROS
#######################################################
add_subdirectory(rosWrapper)

