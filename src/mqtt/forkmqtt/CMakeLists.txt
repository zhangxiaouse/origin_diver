file(GLOB_RECURSE srcs *.cc)
add_library(${PROJECT_NAME}_forkmqtt SHARED ${srcs})
target_link_libraries(${PROJECT_NAME}_forkmqtt
                      ${require_third_libs}
                     )

install(
TARGETS ${PROJECT_NAME}_forkmqtt
ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
                    