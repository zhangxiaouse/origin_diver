file(GLOB_RECURSE srcs *.cc)
project(pub)
add_library(${PROJECT_NAME}_rospublisher SHARED ${srcs})
target_link_libraries(${PROJECT_NAME}_rospublisher
                     )