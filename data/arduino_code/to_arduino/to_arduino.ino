#include <ros.h>
//#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>
#include <Servo.h>

// Define Servo Pins

const uint8_t plat_pin = 3;
const uint8_t shoulder_pin = 5;
const uint8_t forearm_pin = 6;
const uint8_t wrist_pin = 9;

// Create Servo Objects

Servo plat;
Servo shoulder;
Servo forearm;
Servo wrist;



// Initialize ROS paramaters

ros::NodeHandle nh;


//servo callback

void servo_cb(const std_msgs::Int16MultiArray& cmd_msg){

  plat.write(cmd_msg.data[0]);
  shoulder.write(cmd_msg.data[1]);
  forearm.write(cmd_msg.data[2]);
  wrist.write(cmd_msg.data[3]);
  }

// Initialize ros subscriber
ros::Subscriber<std_msgs::Int16MultiArray> servo_sub("servo_cmd", &servo_cb);



void setup() {

  // 57600 or 115200 baud rate?
  nh.getHardware()->setBaud(57600);

  // Attach Servo on pin .. of the Servo Object

  plat.attach(plat_pin);
  shoulder.attach(shoulder_pin);
  forearm.attach(forearm_pin);
  wrist.attach(wrist_pin);
  
  // Hard Start at Horizzontal Position
  
  plat.write(90);
  shoulder.write(90);
  forearm.write(90);
  wrist.write(90);
  
  // ros node setup
  
  nh.initNode();
  
  nh.subscribe(servo_sub);

}

void loop() {

  // spin the ros node
  
  nh.spinOnce();
  delay(20);

}
