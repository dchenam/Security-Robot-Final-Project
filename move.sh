source ../devel/setup.sh
rosrun topic_tools relay /cmd_vel RosAria/cmd_vel &
roslaunch pioneer_2dnav/move_base.launch
