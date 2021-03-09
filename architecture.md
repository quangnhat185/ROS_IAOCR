## Random notes
  - In the arduino code, running `FORWARD` denotes for clockwise rotation and vice versa

## Architecture of the Controller

1. A gamepad is connected with Pi, which published a node `heading_angle` contain the desired heading angle message of the robot (0-360).
2. The ardunio subcribe for the node `heading_angle` to get the heading angle message
3. Base on the angle message, the speed of each wheel is determined. The Arduino engages the motors.
4. The encoder returns the speed of each wheel, the Arduino use a PID controller to regulate it.

## Pseudocode for PID controller
```
class Robot:
  method encoder:
    data current_speed[M1_dot, M2_dot, M3_dot];
    return current_speed;
  
  method set_speed(array[M1, M2, M3] speed):
    speed_1, speed_2, speed_3 = speed;
    motor1.run(speed_1);
    motor2.run(speed_2);
    motor3.run(speed_3);
    
  method PID(array[M1_tar, M2_tar, M3_tar] target_speed):
    feedback_speed = encoder();
    array[M1, M2, M3] input_speed;
    input_speed = pid(input_speed, target_speed);
    self.set_speed(input_speed);
    
main:
  robot = Robot.init();
  while True:
    target_speed = input_from_gamepad();
    robot.PID(target_speed);
```
