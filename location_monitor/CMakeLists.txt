# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(location_monitor)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs nav_msgs)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs nav_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(location_monitor src/location_monitor.cpp)
target_link_libraries(location_monitor ${catkin_LIBRARIES})
add_dependencies(location_monitor location_monitor_generate_messages_cpp)


# %EndTag(FULLTEXT)%
