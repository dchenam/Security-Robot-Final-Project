cmake_minimum_required(VERSION 2.8.3)
project(gspeech)

find_package(catkin REQUIRED)
catkin_package()

## Install
## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
catkin_install_python(PROGRAMS
   gspeech.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
