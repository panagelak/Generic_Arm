cmake_minimum_required(VERSION 2.8.3)
project(arm_bringup)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
)


catkin_package(

)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_Pub_to_Arduino_Class src/pub_to_arduino_class.cpp)

set_target_properties(${PROJECT_NAME}_Pub_to_Arduino_Class PROPERTIES OUTPUT_NAME Pub_to_Arduino_Class PREFIX "")

add_dependencies(${PROJECT_NAME}_Pub_to_Arduino_Class ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


## Specify libraries to link a library or executable target against

target_link_libraries(${PROJECT_NAME}_Pub_to_Arduino_Class
   ${catkin_LIBRARIES}
 )



