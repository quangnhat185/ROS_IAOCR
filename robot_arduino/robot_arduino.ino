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

void serial_print_array(String name,  int arr1[], int arr2[]){
  Serial.print(name + ": ");
  for (int i=0; i<3; i++){
    Serial.print(arr1[i%3]);
    Serial.print(" ");
  }

  for (int i=0; i<3; i++){
    Serial.print(arr2[i%3]);
    Serial.print(" ");
  }
  Serial.println("");
}

class OmniRobot{
  public:
    Adafruit_DCMotor *motor_back = AFMS.getMotor(4);
    Adafruit_DCMotor *motor_right = AFMS.getMotor(3);
    Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
    
    uint8_t binary_to_dict(int b){
      return (b==0)?(FORWARD):(BACKWARD);
    }

    int binary_dict[3];
    int voltage[3];
    int state_vec[3];

    void inverse_kinematic(int state_vec[], int binary_dict[], int voltage[], float l=0.12){

      int v_x = state_vec[0];
      int v_y = state_vec[1];
      int w = state_vec[2];

      int abs_vel[3];
      abs_vel[0] = -v_x/2 - (sqrt(3)*v_y)/2 + l*w;
      abs_vel[1] = v_x + l*w;
      abs_vel[2] = -v_x/2 + (sqrt(3)*v_y)/2 + l*w;    

      for (int i=0; i<3; i++){
        (abs_vel[i]>0)?(binary_dict[i]=0):(binary_dict[i]=1);
        voltage[i] = abs(abs_vel[i]);
      }

    }

  
    void go(int state_vec[], float l=0.12){

      inverse_kinematic(state_vec, binary_dict, voltage);

      serial_print_array("direct/voltage: ", binary_dict, voltage);

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
  nh.getHardware()->setBaud(57600);
  Serial.print("Let the battle begins");
  nh.initNode();
  nh.subscribe(sub);

  AFMS.begin();  // create with the default frequency 1.6KHz
  robot.motor_left->run(RELEASE);
  robot.motor_right->run(RELEASE);
  robot.motor_back->run(RELEASE);
}


void loop() {
  nh.spinOnce();  
  //int dic[3] = {0,0,0};
  //int speed[3] = {200,200,200};
  //robot.go(dic, speed);

  int v_x, v_y;
  v_x,v_y = 150;

  int state_vec[3] = {v_x, v_y, int(angle)};
  
  /*
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
      robot.go(state_vec);
  }
  */
  
  int test[3] = {0,0, int(angle)};
  robot.go(test);
  delay(1);

}
