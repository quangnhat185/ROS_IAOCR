## Architecture of the Controller

1. A gamepad is connected with Pi, which published a node `heading_angle` contain the desired heading angle message of the robot (0-360).
2. The ardunio subcribe for the node `heading_angle` to get the heading angle message
3. Base on the angle message, the speed of each wheel is determined. The Arduino engages the motors.
4. The encoder returns the speed of each wheel, the Arduino use a PID controller to regulate it.