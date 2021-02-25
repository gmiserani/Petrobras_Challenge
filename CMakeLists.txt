cmake_minimum_required(VERSION 3.2.0)
project(petrobras_challenge)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(OpenCV REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp 
  mrs_msgs 
  geometry_msgs 
  gazebo_ros
  std_msgs
  cv_bridge
  gazebo_ros_link_attacher
)

catkin_package (
  CATKIN_DEPENDS
    roscpp 
    mrs_msgs 
    geometry_msgs 
    gazebo_ros
    std_msgs
    cv_bridge
    gazebo_ros_link_attacher
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(qrcode src/qrcode.cpp)
target_link_libraries(qrcode ${catkin_LIBRARIES} ${OpenCV_LIBS} ${ZBAR_LIBRARIES} zbar)

add_executable(nina src/nina.cpp)
target_link_libraries(nina ${catkin_LIBRARIES} ${OpenCV_LIBS} ${ZBAR_LIBRARIES} zbar)

add_executable(controle src/controle.cpp)
target_link_libraries(controle ${catkin_LIBRARIES})
