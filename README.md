# scoring_with_arduino

This package is made for human-robot colift experiments. There are two NRF24L01 transmitters connected to one receiver. Each transmitter sends one button state via RF and the receiver publishes their states to ROS Noetic.



IMPORTANT: Only use Arduino UNO. MEGA is problematic with NRF24L01.



# Installation

These are needed:

- Arduino

  - RF24 (by TMRh20 v.1.4.2)

  - ros_lib: http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

    ```
     1977  git clone https://github.com/ros-drivers/rosserial.git
     1978  cd ..
     1979  catkin_make --only-pkg-with-deps rosserial
     1980  rospack profile 
    ```

- rosserial

  ```
   1775  sudo apt install ros-noetic-rosserial
   1776  sudo apt install ros-noetic-rosserial-arduino
   
   # rosserial_python is not Python3 compatible. Just change the first line of make_libraries.py from "python" to "python3"
   1981  roscd rosserial_python/
   
   1996  rosrun rosserial_arduino make_libraries.py /home/gizem/Arduino/libraries
  ```



# How to

- Upload transmitter and receiver Arduino codes.
- Start Arduino-ROS bridge: `rosrun rosserial_python serial_node.py /dev/ttyACM0`
  - Make sure the receiver Arduino is the port number.



# Known issues

- The system sometimes does not work due to power inconsistencies. The main reason why Mega is problematic is also about that.

  - : https://forum.arduino.cc/t/nrf24l01-stopped-working/234143/6

    "

    Yeah. Plus it is a recurent problem between the Mega and NRF24 module. The Mega just don't supply enogth juice for the NRF24 module on the 3,3volt output pin.

    The usual symptom is that your Mega receive the packet, but is unable to reply back.

    "

- Use capacitors between 3.3V and GND pins pf NRF modules. Currently, I have 33uF and 0.1uF in parallel and works just fine :)

- Do not use `Serial.begin()`or Serial in general. I guess UART pulls so much power. That fucks the NRF antenna power.

- If at some point things stops working again, upload `common_receiver` and `tranmistter-1`. These codes have Serial and interestingly works fine. So, you can debug using these.

