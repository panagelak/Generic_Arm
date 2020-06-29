
#! /bin/bash


x-terminal-emulator -e roslaunch arm_bringup real_bringup.launch 2>/dev/null &&

sleep 3 &&

x-terminal-emulator -e roslaunch moveit_interface moveit.launch 2>/dev/null &&

sleep 2 &&

x-terminal-emulator -e roslaunch arm_viz rviz.launch config:=basic 2>/dev/null &&

sleep 5 &&

x-terminal-emulator -e rosrun moveit_interface set_start_pos.py 2>/dev/null &


