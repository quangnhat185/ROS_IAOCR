#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor_back = AFMS.getMotor(4);
Adafruit_DCMotor *motor_right = AFMS.getMotor(3);
Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(57600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  //myMotor->setSpeed(150);
  //myMotor->run(FORWARD);
  // turn on motor
  //myMotor->run(RELEASE);
   motor_left->run(RELEASE);
   motor_right->run(RELEASE);
   motor_back->run(RELEASE);
}

void loop() {

  motor_left->run(BACKWARD);
  motor_right->run(BACKWARD);
  motor_back->run(BACKWARD);
  
  motor_left->setSpeed(150);
  motor_right->setSpeed(150);
  motor_back->setSpeed(150);
  
  delay(5000);
  motor_left->setSpeed(0);
  motor_right->setSpeed(0);
  motor_back->setSpeed(0);
  delay(5000);

}
