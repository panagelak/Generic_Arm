
#! /bin/bash


x-terminal-emulator -e roslaunch arm_bringup sim_bringup.launch world:=empty 2>/dev/null &&

sleep 10 &&

x-terminal-emulator -e roslaunch moveit_interface moveit.launch 2>/dev/null &&

sleep 2 &&

x-terminal-emulator -e rosrun moveit_interface set_start_pos.py 2>/dev/null &&

sleep 1 &&

x-terminal-emulator -e roslaunch sensor_stick object_recognition.launch 2>/dev/null &&

sleep 5 &&

x-terminal-emulator -e roslaunch arm_viz rviz.launch config:=object_recognition 2>/dev/null &&

sleep 5 &&

x-terminal-emulator -e roslaunch moveit_interface pick_place.launch 2>/dev/null &&

sleep 5 &&

x-terminal-emulator -e rosrun moveit_interface pick_place_client.py 2>/dev/null &






