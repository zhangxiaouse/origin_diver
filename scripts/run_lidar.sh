source ./devel/setup.bash
# pointlcoud2 ,used for localziation
gnome-terminal --tab --title "lidar driver" -e 'bash -c "roslaunch livox_ros_driver2 rviz_MID360.launch rviz_enable:=true "'

# livox format ,used for mapping
# gnome-terminal --tab --title "lidar driver" -e 'bash -c "roslaunch livox_ros_driver2 msg_MID360.launch "' 