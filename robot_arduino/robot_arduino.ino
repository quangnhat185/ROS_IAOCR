#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

class OmniRobot{
  public:
    Adafruit_DCMotor *motor_back = AFMS.getMotor(4);
    Adafruit_DCMotor *motor_right = AFMS.getMotor(3);
    Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
    
    uint8_t binary_to_dict(int b){
      return (b==0)?(FORWARD):(BACKWARD);
    }

    void go(int binary_dict[3], int voltage[3]){
      
      //motor_left->run(binary_to_dict(binary_dict[0]));
      motor_left->run(binary_to_dict(binary_dict[0]));
      motor_left->setSpeed(voltage[0]);

      motor_right->run(binary_to_dict(binary_dict[1]));
      motor_right->setSpeed(voltage[1]);

      motor_back->run(binary_to_dict(binary_dict[2]));
      motor_back->setSpeed(voltage[2]);
    }

    void stop(){
      motor_left->setSpeed(0);
      motor_right->setSpeed(0);
      motor_back->setSpeed(0);
    }
};

// Select which 'port' M1, M2, M4
OmniRobot robot;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor");
  AFMS.begin();  // create with the default frequency 1.6KHz
  robot.motor_left->run(RELEASE);
  robot.motor_right->run(RELEASE);
  robot.motor_back->run(RELEASE);
}


void loop() {
  int dic[3] = {0,0,0};
  int speed[3] = {200,200,200};
  //robot.go(dic, speed);
  robot.stop();
  delay(5000);

}
