#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

ros::NodeHandle nh;

int speed;
void message(const std_msgs::UInt16 & cmd_msg){
  speed = cmd_msg.data;
}

ros::Subscriber<std_msgs::UInt16> sub("heading_angle", message);

void setup() {
  // put your setup code here, to run once:
  AFMS.begin(); 
  
  nh.initNode();
  nh.subscribe(sub);
  
  myMotor->run(FORWARD);
  myMotor->run(RELEASE);

}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();  
  delay(1);
  myMotor->run(FORWARD);
  myMotor->setSpeed(speed);
  
}
