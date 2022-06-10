/*
   Button Example for Rosserial
*/

#include <ros.h>
#include <std_msgs/Int8MultiArray.h>


ros::NodeHandle nh;

std_msgs::Int8MultiArray button_msg;
ros::Publisher pub_multiarray("arduino_multiarray_publisher", &button_msg);

int16_t button_arr[2] = {5, 5}; // before no data arrived, the button values are 5 (dummy)

void setup()
{
  nh.initNode();
  nh.advertise(pub_multiarray);
}

void loop()
{
  button_msg.data[0] = button_arr[0];
  button_msg.data[1] = button_arr[2];
  button_msg.data_length = 2;

  pub_multiarray.publish(&button_msg);

  nh.spinOnce();
  delay(1000);
}
