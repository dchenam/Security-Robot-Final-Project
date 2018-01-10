cmake_minimum_required(VERSION 2.8.3)
project(person)

find_package(catkin REQUIRED COMPONENTS)

catkin_package()
catkin_install_python(PROGRAMS
   person.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
