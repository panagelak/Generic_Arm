# Connect any Arm with ROS

**This Project is a KickOff Project of my Open Mobile Manipulator Project**

[Open Mobile Manipulator Project](https://github.com/panagelak/Open_Mobile_Manipulator)

## Description

**This project is meant to help you with connecting ANY DIY ARM with feedback or not to ROS , both in simulation and on reality!!**

![Generic Arm](data/img/rviz_robot.png)
![Pick Place](data/img/pick_place_server.png)

## URDF

**The idea is that you can customize the  URDF of the arm to resemble your robot, IF you see  in the arm_description package on the robots folder there is a configuration file with some global properties that all the macros have access too, In order to easily change the properties of the arm.**

**I think i have made a good job of this**

## Hardware Interface

**I have used this hardware interface from  PickNikRobotics P.S I didn't fork in order to have it all in a single git repo sorry**

[Hardware Interface](https://github.com/PickNikRobotics/ros_control_boilerplate)

**Right now in the read and write function i have just include a passthrough code which assumes perfect execution with position**

**e.g joint_position_[joint_id] = joint_position_command_[joint_id];**

**With this you can move the robot using ONLY RViz with ros_control or MoveIt instead of using Gazebo and ros_control_plugin**

**If you then want to control a real robot arm without feedback all you have to do is to transform the joint_states into appropiate servo commands and send them to the robot for execution with e.g rosserial, I have included an example of such a node in the arm_bringup package and the corresponding arduino code in the data folder and how to launch them in the real_bringup.launch**

**I would also like to put a publisher and subscriber inside the hardware interface so you can do something similar with robot that have feedback on the servos or whatever. Not the fastest but it will work**

## 3D Perception

**I have Included a 3D Perception package sensor_stick it is a mod of the Udacity's Robotic's Nanodegree 3D Perception Project **

**The idea is that you capture features (hsv and surface normal features in a histogram format) in a Gazebo world and outputs a training_set.sav file**

**$ roslaunch sensor_stick training.launch**
**$ rosrun sensor_stick capture_features.py**

![](data/gifs/training_extract_features.gif)

**Then with that features we train an SVM with linear kernel Classifier which outputs the classifier in a model.sav file**

 **$ rosrun sensor_stick train_svm.py**

**Then we can use this classifier in our perception pipeline e.g prefiltering -> segmentation -> classify -> publish tf and markers**

**$ roslaunch sensor_stick object_recognition.launch**

![](data/gifs/Object_Recognition.gif)

**P.S In order to run it you will need to be able to import pcl and sklearn in python2 (see my Open Mobile Manipulator Project on how to install pcl in python)**

### Install 3D Perception

**In your .bashrc**

export GAZEBO_MODEL_PATH=~/catkin_ws/src/arm/sensor_stick/models:$GAZEBO_MODEL_PATH

**Go to this package [RoboND-Install-PCL](https://github.com/udacity/RoboND-Perception-Exercises) clone in a different folder and follow the instruction there in order to install pcl**

**You will also need to install sklearn in python2**

## For simulation

**$ roslaunch arm_bringup sim_bringup.launch**

Gazebo world + Black Box + Robot description + Camera with Ros Controllers

**$ roslaunch moveit_interface moveit.launch**

Launches the MoveGroup

**$ rosrun moveit_interface set_start_pos.py**

Set's the arm to the start position

**$ roslaunch arm_viz rviz.launch config:=basic**

Launches RViz with a predefined configuration

## For real robot run the command

**$ roslaunch arm_bringup real_bringup.launch**

Launches the Robot Description + Robot Hardware Interface + Robot Controllers

**$ roslaunch moveit_interface moveit.launch**

**$ rosrun moveit_interface set_start_pos.py**

**$ roslaunch arm_viz rviz.launch config:=basic**

## Scripting

**Instead of opening multiple terminals and writing the commands 1 by 1**

**It is a good practice to use script files to launch automatically multiple terminals with your desired commands by simple running the script**

**Make sure you have installed xterm emulator**

**sudo apt-get update -y**

**sudo apt-get install -y x-terminal-emulator**

**also your scripts (and .py) files have permissions**

**chmod +x safe_spawner_basic.sh**


**To that end you can go to ( $ roscd safe_spawner ) there you will find some scripts - demos that you can run, for example**

**1. $ ./safe_spawner_basic.sh** :  Will launch the sim_bringup with an empty world + Moveit + Start pos + RViz

**2. $ ./safe_spawner_pseudo_real.sh**  Will launch real_bringup + moveit + rviz (SEE HOW THE ARM MOVES USING ONLY RViz)

**3. $ ./safe_spawner_object_recognition.sh**  Will launch sim_bringup + Moveit + Start pos + 3D Perception + Pick n Place Server + Pick n Place Client + Rviz (See 3D Perception + Click next in RViz)

**I will make more of this in the feature**
 
## Compiling

**mkdir -p ~/catkin_ws/src && cd catkin_ws/src**

**git clone** https://github.com/panagelak/Generic_Arm.git

**cd ~/catkin_ws**

**rosdep install --from-paths src --ignore-src -r -y** (install depedencies)

**catkin_make**

**Now theoritically it will be easy to compile the project in ROS Melodic, where you might find some problem in execution is with the sensor_stick package, you will need to be able to import in python pcl and sklearn**

## Arduino Code

**In the data folder you will find an example of an arduino code that you can use to control servos with the Servo library although the best option would be to use a PCA9685 i2c Servo driver for this purpose**


## Contact ME

**You can contact me at panagelak12@gmail.com or panagiotis.angelakis.robot@gmail.com**

**For more assembly details or questions**

**I will be happy to answer your questions don't be afraid!!!**

**Cheers**nd whether it will instantiate this gazebo macro**
## 3D Perception

**Step 1 : Extract Features**

**$ roslaunch sensor_stick training.launch**

This will a simple Gazebo world with sensor stick and an RGB camera

Then you can run the node capture features which will spawn the objects in random orientations and extract the features, when this node is done it will output a training_set.sav file.

**$ rosrun sensor_stick capture_features.py**

Have a look at this node, more orientation the better, you can add your own models at sensor_stick/models  directory put at your bashrc the following 

export GAZEBO_MODEL_PATH=~/catkin_ws/src/Open_Mobile_Manipulator/sensor_stick/models:$GAZEBO_MODEL_PATH

P.S you can also download the osrf gazebo models (optional)

**Step 2: Train the SVM classifier**

Then with the training_set.sav file ready we are ready to train our SVM classifier. Run the node

**$ rosrun sensor_stick train_svm.py**

Make sure, the training_set.sav is in a location that pickle can read.
It will output a model.sav file containing the classifier.

**Step 3 : Run the object recognition pipeline**

**$ roslaunch sensor_stick object_recognition.launch**

**P.S for a demo you can also run the associated script**

Then you will see your object recognized with labels on RVIZ and associating TF's





## Jetson Nano problem with kinect?

I had a problem with the Openni driver on the jetson nano which runs ros melodic, i think they have not properly build the driver for arm processors.

To overcome this i used a simple Docker image that you can find on the DockerFile folder. Jetson Nano comes with docker installed otherwise install it.

to build the image run from inside the DockerFile dir

**$ docker build -t kinect_image:1.0 .**

Then you can run the image and get the kinect topics with the following command

**$ sudo docker run --net=host --privileged kinect_image:1.0**
 
## Compiling

**mkdir -p ~/catkin_ws/src && cd catkin_ws/src**

**git clone** https://github.com/panagelak/Open_Mobile_Manipulator.git

**cd ~/catkin_ws**

**rosdep install --from-paths src --ignore-src -r -y** (install depedencies)

**catkin_make**

**Now theoritically it will be easy to compile the project in ROS Melodic, where you might find some problem is with the sensor_stick package, you will need to be able to import in python pcl and sklearn**

**Go to this package [RoboND-Install-PCL](https://github.com/udacity/RoboND-Perception-Exercises) clone in a different folder and follow the instruction there in order to install pcl**

**Then install somehow sklearn you can use conda maybe?**

## Arduino Due

Download Arduino IDE then download in the board manager the board for the due

Programming port - Arduino due , port devttyACM0 -> Upload the arduino code

In the arduino_code folder you can find the Arduino libraries i used that you should copy paste on your arduino scetch folder.

**It is advised to ude Arduino DUE, both because it is faster, which gives you the flexibillity to read the 4 quadrature encoders directly and because it has better compatibillity with rosserial, also for rosserial add this line on the top of your scetch #define USE_USBCON**

**sudo usermod -a -G dialout $USER** restart


![Arduino Scetch](data/ommp_bb.jpg)

![Power Scetch](data/power_connections.jpg)

##Real ros_control hardware Interface of the arm

I used this repo of  [**PickNikRobotics**](https://github.com/PickNikRobotics/ros_control_boilerplate) , I should have forked but this is complicated :)

Follow the instructions on this repo, i just deleted some testing stuff because i couldn't compile it, then i renamed the files as he describes!

Because my arm doesn't have feedback on the read and write i just pass the position_command_interface into the joint_state_interface, this is to say we assume perfect execution.

This also has the effect that the robot-rviz (meaning what the robot thinks), thinks that the arm is moving (joint_states), whether you have the real arm connected or not (you can see it moving in rviz)

After that i used a node that subscribes to the joint_states, transforms them into appropiate servo commands and sends them to rosserial for execution in a Multiarray message. You can find this node at ommp_bringup/src/pub_to_arduino_class.cpp

Meaning that the arm is a "clone" of the joint_states. Furthermore, on the rosserial code there is a call activate_arm if you publish an integer on this topic, it will activate the servos in a predefined position, that is approximately the same with the starting position mentioned before.

In order to avoid sudden movements of the arm, first command the arm with moveit to go to that start_position then activate the servos. Now your arm is synchronized with the joint_States and can clone them!!!

See the lynbot_bringup.launch on how to launch the hardware interface



## List of materials
[Geared dc motor x4](https://www.robotshop.com/eu/en/lynxmotion-12vdc-200rpm-078kg-cm-ghm-16-w--rear-shaft.html)

[quadrature encoder x4](https://www.robotshop.com/eu/en/lynxmotion-quadrature-motor-encoder-v2-cable.html)

[arm 6 dof amazon uk](https://www.amazon.co.uk/gp/product/B07VYHFL1V/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)

Jetson Nano ~ 100

Arduino Due ~ 30

4 L298N motor driver

3 DC-DC buck converters

2D ydlidar ~ 100

1 lipo 5000 mah battery ~ 50

1 usb wifi anttena

1 16-bit Adafruit servo shield I2c or HCPCA9685

**The total cost should be approximately 500 - 700 euro**


## Robot Base

The robot base will consist of two levels of wood e.g 40x20 cm.

In the lower level put 4 dc motor brackets (below) and make holes for the cables.

Make 8mm holes to pass through metal rods and nuts (maybe put glue too)

In the lower level put the lidar **elevated** maybe with 3 small pieces of wood and double side tape, also the arduino due,L298N and battery

In the upper level place the 3 DC-DC buck converters and Jetson Nano, arm

e.g You can make an elevated platform for kinect above the upper level with 3 extra metal threads

**BE CREATIVE**

## Diploma

**In this repo you can find my Diploma there you can find a lot of theory and some experimental results on the appendix!!!**

## Contact ME

**You can contact me at panagelak12@gmail.com or panagiotis.angelakis.robot@gmail.com**

**For more assembly details or questions**

**I will be happy to answer your questions don't be afraid!!!**

**Cheers**See the lynbot_bringup.launch on how to launch the hardware interface



## List of materials
[Geared dc motor x4](https://www.robotshop.com/eu/en/lynxmotion-12vdc-200rpm-078kg-cm-ghm-16-w--rear-shaft.html)

[quadrature encoder x4](https://www.robotshop.com/eu/en/lynxmotion-quadrature-motor-encoder-v2-cable.html)

[arm 6 dof amazon uk](https://www.amazon.co.uk/gp/product/B07VYHFL1V/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)

Jetson Nano ~ 100

Arduino Due ~ 30

4 L298N motor driver

3 DC-DC buck converters

2D ydlidar ~ 100

1 lipo 5000 mah battery ~ 50

1 usb wifi anttena

1 16-bit Adafruit servo shield I2c or HCPCA9685

**The total cost should be approximately 500 - 700 euro**


## Robot Base

The robot base will consist of two levels of wood e.g 40x20 cm.

In the lower level put 4 dc motor brackets (below) and make holes for the cables.

Make 8mm holes to pass through metal rods and nuts (maybe put glue too)

In the lower level put the lidar **elevated** maybe with 3 small pieces of wood and double side tape, also the arduino due,L298N and battery

In the upper level place the 3 DC-DC buck converters and Jetson Nano, arm

e.g You can make an elevated platform for kinect above the upper level with 3 extra metal threads

**BE CREATIVE**

## Diploma

**In this repo you can find my Diploma there you can find a lot of theory and some experimental results on the appendix!!!**

## Contact ME

**You can contact me at panagelak12@gmail.com or panagiotis.angelakis.robot@gmail.com**

**For more assembly details or questions**

**I will be happy to answer your questions don't be afraid!!!**

**Cheers**ur questions don't be afraid!!!**

**Cheers** cost should be approximately 500 - 700 euro**


## Robot Base

The robot base will consist of two levels of wood e.g 40x20 cm.

In the lower level put 4 dc motor brackets (below) and make holes for the cables.

Make 8mm holes to pass through metal rods and nuts (maybe put glue too)

In the lower level put the lidar **elevated** maybe with 3 small pieces of wood and double side tape, also the arduino due,L298N and battery

In the upper level place the 3 DC-DC buck converters and Jetson Nano, arm

e.g You can make an elevated platform for kinect above the upper level with 3 extra metal threads

**BE CREATIVE**

## Diploma

**In this repo you can find my Diploma there you can find a lot of theory and some experimental results on the appendix!!!**

## Contact ME

**You can contact me at panagelak12@gmail.com or panagiotis.angelakis.robot@gmail.com**

**For more assembly details or questions**

**I will be happy to answer your questions don't be afraid!!!**

**Cheers**ur questions don't be afraid!!!**

**Cheers**