
#! /bin/bash


x-terminal-emulator -e roslaunch arm_bringup sim_bringup.launch world:=empty 2>/dev/null &&

sleep 8 &&

x-terminal-emulator -e roslaunch moveit_interface moveit.launch 2>/dev/null &&

sleep 2 &&

x-terminal-emulator -e rosrun moveit_interface set_start_pos.py 2>/dev/null &&

sleep 1 &&

x-terminal-emulator -e roslaunch arm_viz rviz.launch config:=basic 2>/dev/null &



