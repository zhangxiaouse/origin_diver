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


  # ----------------------------------------------
add_definitions(-D_REPO_NAME=\"${CMAKE_CURRENT_LIST_DIR}\")
# ----------------------------
execute_process(
COMMAND git rev-parse --abbrev-ref HEAD
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
OUTPUT_VARIABLE GIT_BRANCH
ERROR_QUIET
OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions(-D_GIT_BRANCH=\"${GIT_BRANCH}\")

# 检查是否存在 GIT_BRANCH 变量
if (DEFINED GIT_BRANCH)
  message("12")
    # 打开一个文件用于写入，如果不存在则创建
    file(APPEND "git_branch.txt" "${GIT_BRANCH}")
else()
 message("21")
    message(FATAL_ERROR "GIT_BRANCH 变量未定义。请确保在执行 CMake 时获取 Git 分支信息。")
endif()


# ----------------------------
execute_process(
COMMAND git describe --abbrev=4 --dirty --always --tags
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
OUTPUT_VARIABLE GIT_TAG
ERROR_QUIET
OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions(-D_GIT_TAG=\"${GIT_TAG}\")

# 检查是否存在 GIT_BRANCH 变量
if (DEFINED GIT_BRANCH)
  message("12")
    # 打开一个文件用于写入，如果不存在则创建
    file(APPEND "git_branch.txt" "${GIT_TAG}\n")
else()
 message("21")
    message(FATAL_ERROR "GIT_BRANCH 变量未定义。请确保在执行 CMake 时获取 Git 分支信息。")
endif()

# ----------------------------
execute_process(
COMMAND git rev-parse HEAD
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
OUTPUT_VARIABLE GIT_COMMIT
ERROR_QUIET
OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions(-D_GIT_COMMIT="${GIT_COMMIT}")
# 检查是否存在 GIT_BRANCH 变量
if (DEFINED GIT_BRANCH)
  message("12")
    # 打开一个文件用于写入，如果不存在则创建
    file(APPEND "git_branch.txt" "${GIT_COMMIT}\n")
else()
 message("21")
    message(FATAL_ERROR "GIT_BRANCH 变量未定义。请确保在执行 CMake 时获取 Git 分支信息。")
endif()

execute_process(
    COMMAND git log -n 10 --pretty=format:"%h %an %cd %s"
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_LOG_OUTPUT
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (GIT_LOG_OUTPUT)
file(APPEND "git_branch.txt" "${GIT_LOG_OUTPUT}\n")

    # 打印Git提交日志
    message("Git提交日志:\n${GIT_LOG_OUTPUT}")
else()
    message(WARNING "无法获取Git提交日志。")
endif()

# ----------------------------------------------

# 添加一个自定义命令来计算MD5哈希值
add_custom_command(
    TARGET tracer
    POST_BUILD
    COMMAND md5sum $<TARGET_FILE:tracer> > md5.txt
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Calculating MD5 hash of tracer"
)