source ../../devel/setup.bash

gnome-terminal \
--tab --title "lidar driver" -e 'bash -c "roslaunch livox_ros_driver2 rviz_MID360.launch;exec bash "' \
--tab --title "serial driver" -e 'bash -c "sleep 3; roslaunch serial_rs232 serial_pub_sub.launch ;exec bash "' \

