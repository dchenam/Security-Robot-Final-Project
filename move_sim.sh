source ../devel/setup.sh
rosrun topic_tools relay /cmd_vel /r1/cmd_vel &
rosrun topic_tools relay r1/front_laser/scan scan &
roslaunch my_gazebo_2dnav/move_base.launch
