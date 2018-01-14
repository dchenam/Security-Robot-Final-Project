sudo chmod 777 /dev/ttyUSB0
sudo chmod 777 /dev/ttyACM0
sudo chmod 777 /dev/input/js0
roslaunch launch/master.launch
export ROS_IP=192.168.0.113
export ROS_MASTER_URI=http://192.168.0.113:11311 

