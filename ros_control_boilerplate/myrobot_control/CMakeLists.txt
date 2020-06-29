include_directories(
  include/
)

# MyRobot Hardware Interface
add_library(myrobot_hw_interface
  src/myrobot_hw_interface.cpp
)
target_link_libraries(myrobot_hw_interface
  generic_hw_interface
  ${catkin_LIBRARIES}
)

# Main control executable
add_executable(myrobot_hw_main src/myrobot_hw_main.cpp)
target_link_libraries(myrobot_hw_main
  myrobot_hw_interface
  generic_hw_control_loop
  ${catkin_LIBRARIES}
)

## Install ------------------------------------------------------------

# Install libraries
install(TARGETS
    myrobot_hw_interface
  LIBRARY DESTINATION
    ${CATKIN_PACKAGE_LIB_DESTINATION}
)

# Install executables
install(TARGETS
    myrobot_hw_main
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Install header files
install(DIRECTORY include/myrobot_control/   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
