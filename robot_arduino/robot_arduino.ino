#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
ros::NodeHandle nh;

// gloabl variable  angle
unsigned int angle;

// callback funtion to derive data  from Pi
void message(const std_msgs::UInt16 & cmd_msg){
  angle = cmd_msg.data;
}

ros::Subscriber<std_msgs::UInt16> sub("heading_angle", message);

class OmniRobot{
  public:
    Adafruit_DCMotor *motor_back = AFMS.getMotor(4);
    Adafruit_DCMotor *motor_right = AFMS.getMotor(3);
    Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
    
    uint8_t binary_to_dict(int b){
      return (b==0)?(FORWARD):(BACKWARD);
    }
  
  void go(int v_x=150, int v_y=150, int w=0, float l=0.12){

    int v1, v2, v3;   

    v1 = -v_x/2 - (sqrt(3)*v_y)/2 + l*w;
    v2 = v_x + l*w;
    v3 = -v_x/2 + (sqrt(3)*v_y)/2 + l*w;    

    int velocity[3] = {v1, v2, v3};
    int binary_dict[3];
    int voltage[3];

    for (int i=0; i<3; i++){
      (velocity[i]>0)?(binary_dict[i] = 0):(binary_dict[i] = 1);
      voltage[0] = abs(velocity[i]);
    }

    //motor_left->run(binary_to_dict(binary_dict[0]));
    motor_left->run(binary_to_dict(binary_dict[0]));
    motor_left->setSpeed(voltage[0]);

    motor_right->run(binary_to_dict(binary_dict[1]));
    motor_right->setSpeed(voltage[1]);

    motor_back->run(binary_to_dict(binary_dict[2]));
    motor_back->setSpeed(voltage[2]);
  }

    void turn_left(int speed=150){      
      motor_left->run(FORWARD);
      motor_left->setSpeed(speed);

      motor_right->run(FORWARD);
      motor_right->setSpeed(speed);

      motor_back->run(FORWARD);
      motor_back->setSpeed(speed);
    }

    void turn_right(int speed=150){
      motor_left->run(BACKWARD);
      motor_left->setSpeed(speed);

      motor_right->run(BACKWARD);
      motor_right->setSpeed(speed);

      motor_back->run(BACKWARD);
      motor_back->setSpeed(speed);
    }    

    void stop(){
      motor_left->run(RELEASE);
      motor_right->run(RELEASE);
      motor_back->run(RELEASE);
    }
};

// Select which 'port' M1, M2, M4
OmniRobot robot;

void setup() {
  Serial.begin(57600);           // set up Serial library at 57600 bps
  Serial.print("Let the battle begins")
  nh.initNode();
  nh.subscribe(sub);

  AFMS.begin();  // create with the default frequency 1.6KHz
  robot.motor_left->run(RELEASE);
  robot.motor_right->run(RELEASE);
  robot.motor_back->run(RELEASE);
}g


void loop() {
  nh.spinOnce();  
  //int dic[3] = {0,0,0};
  //int speed[3] = {200,200,200};
  //robot.go(dic, speed);
  Serial.println(angle);
  
  switch(angle){
    case 720:
      robot.turn_right();
      break;
    case 360:
      robot.turn_left();
      break;
    case 0:
      robot.stop();
      break;
    default:
      robot.go(angle);
  }
  
  delay(1);

}
