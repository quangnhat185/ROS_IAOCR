## The ROS packages for IAOCRs

- ip: 10.111.14.11
- username: ubuntu@omnirobot
- password: robotics

## To do list
- [x] Publish the heading angle (0-360) from Pi. Node name: `heading_angle`
- [x] Arduino subcribe for the heading angle
- [ ] Use Joystick 
- [ ] Arduino uses the heading angle to determine the speed of each motor
- [ ] Arduino use PID to reguglate the speed of each motor via encoder

## Notes
- In the arduino code, running `FORWARD` denotes for clockwise rotation and vice versa

- Object robot contains following functions:
    - `robot.go([left_motor_direction,righ_motor_direction,back_motor_direction],[left_motor_speed,right_motor_speed,back_motor_speed])`, where:
        -` <motor>_direction` = 0 (1) : GO FORWARD (BACKWARD)
        - `<motor>_speed`: 0 - 255
    - `robot.stop()`: stop the robot
## Resources
- [Rosserial Arduino](http://wiki.ros.org/rosserial_arduino/Tutorials)

## Frequent usage command lines
- `$ sudo chmod a+rw /dev/ttyACM0`  # permission for Arduino board to be uploaded
- `$ rosrun rosserial_python serial_node.py /dev/ttyACM0` # intitialize serial communication
