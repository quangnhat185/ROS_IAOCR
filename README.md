## The ROS packages for IAOCR

- ip: 10.111.14.11
- username: ubuntu@omnirobot
- password: robotics

## To do list
- [x] Publish the heading angle (0-360) from Pi. Node name: `heading_angle`
- [x] Arduino subcribe for the heading angle
- [ ] Use Joystick 
- [ ] Arduino uses the heading angle to determine the speed of each motor
- [ ] Arduino use PID to reguglate the speed of each motor via encoder

## Resources
- [Rosserial Arduino](http://wiki.ros.org/rosserial_arduino/Tutorials)

## Frequent usage command lines
- `$ sudo chmod a+rw /dev/ttyACM0A`  # permission for Arduino board to be uploaded
- `$ rosrun rosserial_python serial_node.py /dev/ttyACM0` # intitialize serial communication
