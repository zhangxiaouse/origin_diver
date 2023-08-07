file(GLOB_RECURSE srcs *.cc)
add_library(${PROJECT_NAME}_forkmqtt SHARED ${srcs})
target_link_libraries(${PROJECT_NAME}_forkmqtt
                      ${require_third_libs}
                     )