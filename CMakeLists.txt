cmake_minimum_required(VERSION 2.8.3)
project(obstacle_detection)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  geometry_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(obstacle_detect src/obstacle_detect.cpp)
target_link_libraries(obstacle_detect ${catkin_LIBRARIES})
