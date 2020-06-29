#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int16MultiArray.h"

class arduinoHandler {
public:
  // Constructor
  arduinoHandler() {
    js_sub = nh.subscribe("/joint_states", 10, &arduinoHandler::jsCB, this);
    arm_pub = nh.advertise<std_msgs::Int16MultiArray>("/servo_cmd", 10);
  }
  // Mapping Function
  int map(float inValue, float minOutRange, float maxOutRange) {

    // When inValue = 0 -> we want 90
    // 1.5 = 85.94 degrees in order for the servo to move this deggres it needs an
    // offset command of 85.94/1.5 = 57.29
    // When inValue = 1.5 -> we want 90 + 57.29 = 147.29
    // When inValue = -1.5 -> we want 90 - 57.29 = 32.70

    float minInRange = -1.5; // Minimum Joint_state Value
    float maxInRange = 1.5;  // Maximum Joint_state Value
    float x = (inValue - minInRange) / (maxInRange - minInRange);
    float result = minOutRange + (maxOutRange - minOutRange) * x;
    return int(result);
  }
  // Mapp Gripper NOT used for now!!
  int map_gripper(float inValue, float minOutRange, float maxOutRange) {
    // joint_state goes from 0 to 0.02 we map 0 to upper and 0.02 to lower
    float minInRange = 0.0;
    float maxInRange = 0.02;
    float x = (inValue - minInRange) / (maxInRange - minInRange);
    float result = minOutRange + (maxOutRange - minOutRange) * x;
    return int(result);
  }
  
  // Subscriber to Joint States -> Publish to arduino "servo_cmd" topic
  void jsCB(const sensor_msgs::JointState::ConstPtr &joint_state) {
  	// Initialize array
    std_msgs::Int16MultiArray arm_array;
    arm_array.data.clear();
    
    // Get Current joint_states values
    curr_0 = joint_state->position[1];  // plat in pos 1 of joint_States topic..
    curr_1 = joint_state->position[2];  // shoulder in pos2 of joint_States topic..
    curr_2 = joint_state->position[0];  // forearm in pos 0 of joint_states topic..
    curr_3 = joint_state->position[3];  // wrist in pos 3 of joint_States topic..

    // Conditions to check if any joint has moved from the previous callback
    bool cond_0 = fabs(prev_0 - curr_0) < 0.001;
    bool cond_1 = fabs(prev_1 - curr_1) < 0.001;
    bool cond_2 = fabs(prev_2 - curr_2) < 0.001;
    bool cond_3 = fabs(prev_3 - curr_3) < 0.001;

    // If the arm hasn't move no need to publish anything just Return
    if (cond_0 && cond_1 && cond_2 && cond_3) {
      return;
    }
    
    // Map the joint_states into appropiate Servo commands for the Servo Arduino library
    
    // If you want to reverse direction do
    // int servo_0 = 180 - this->map(curr_0, 32.70, 147.29);
    int servo_0 = this->map(curr_0, 32.70, 147.29);  //plat
    int servo_1 = this->map(curr_1, 32.70, 147.29);  //shoulder
    int servo_2 = this->map(curr_2, 32.70, 147.29);  // forearm
    int servo_3 = this->map(curr_3, 32.70, 147.29);  // wrist


    // Populate the Array
    arm_array.data.push_back(servo_0);
    arm_array.data.push_back(servo_1);
    arm_array.data.push_back(servo_2);
    arm_array.data.push_back(servo_3);

    // Publish the Array
    arm_pub.publish(arm_array);
    
    // Store the Current Joint_state into Previous Joint_states
    prev_0 = curr_0;
    prev_1 = curr_1;
    prev_2 = curr_2;
    prev_3 = curr_3;

  }

protected:
  // Ros Stuff
  ros::NodeHandle nh;
  ros::Subscriber js_sub;
  ros::Publisher arm_pub;
  float curr_0 = 0, curr_1 = 0, curr_2 = 0, curr_3 = 0;
  float prev_0 = 0, prev_1 = 0, prev_2 = 0, prev_3 = 0;


};

int main(int argc, char **argv) {
  // Start the Node
  ros::init(argc, argv, "driver_to_arduino");
  // Initialize an Object to our Class
  arduinoHandler handler;
  ros::spin();
  return 0;
}
