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

    void assign_array(int arr1[], int arr2[]){
      for (int i=0; i<3; i++){
        arr1[i]=arr2[i];
      }
    }

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

    void control_from_gamepad(unsigned int heading, int binary_dict[], int voltage[], int base_speed=200){
      // Up
      if ((170<heading) && (heading<190))
      {
        int dir[3] = {0,1,0};
        int vel[3] = {base_speed, base_speed,0};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);             
      }// South-East
      else if ((10<heading) && (heading<80)){
        int dir[3] = {1,0,1};
        int vel[3] = {base_speed/2, base_speed,base_speed};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);                      
      }// Right
      else if ((80<heading) && (heading<100)){
        int dir[3] = {0,0,1};
        int vel[3] = {base_speed/2, base_speed/2,base_speed};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);            
      }// North-East      
      else if ((100<heading) && (heading<170)){
        int dir[3] = {0,1,1};
        int vel[3] = {base_speed, base_speed/2,base_speed};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);            
      }//North-West
      else if ((190<heading) && (heading<260)){
        int dir[3] = {0,1,0};
        int vel[3] = {base_speed/2, base_speed,base_speed};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);            
      } // Left
      else if ((260<heading) && (heading<280)){
        int dir[3] = {1,1,0};
        int vel[3] = {base_speed/2, base_speed/2,base_speed};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);            
      } // South-West
      else if ((280<heading) && (heading<350)){
        int dir[3] = {1,0,0};
        int vel[3] = {base_speed, base_speed/2,base_speed};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);            
      }// Down
      else if (heading==1000){
        int dir[3] = {1,0,0};
        int vel[3] = {base_speed, base_speed,0};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);          
      }else{
        int dir[3] = {0,0,0};
        int vel[3] = {0,0,0};
        assign_array(binary_dict,dir);
        assign_array(voltage, vel);   
      }

      // serial_print_array("direct/voltage: ", binary_dict, voltage);                             
    }

    
    void go(unsigned int heading, int base_speed=200, float l=0.12){

      //inverse_kinematic(state_vec, binary_dict, voltage);
      control_from_gamepad(heading, binary_dict, voltage, base_speed);

      //serial_print_array("direct/voltage: ", binary_dict, voltage);

      //motor_left->run(binary_to_dict(binary_dict[0]));
      motor_left->run(binary_to_dict(binary_dict[0]));
      motor_left->setSpeed(voltage[0]);

      motor_right->run(binary_to_dict(binary_dict[1]));
      motor_right->setSpeed(voltage[1]);

      motor_back->run(binary_to_dict(binary_dict[2]));
      motor_back->setSpeed(voltage[2]);
    }

    void rotate_left(int speed=150){      
      motor_left->run(FORWARD);
      motor_left->setSpeed(speed);

      motor_right->run(FORWARD);
      motor_right->setSpeed(speed);

      motor_back->run(FORWARD);
      motor_back->setSpeed(speed);
    }

    void rotate_right(int speed=150){
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

  /*
  if (angle==720){
    robot.rotate_right();
  }
  else if (angle==360){
    robot.rotate_left();
  }else if (angle==0){
    robot.stop();
  }else{
    robot.go(angle);
  }
  delay(10);
  */

  switch(angle){
    case 720:
      robot.rotate_right();
      break;
    case 360:
      robot.rotate_left();
      break;      
    case 0:
      robot.stop();
      break;
    default:
      robot.go(angle);
  }
  delay(10);
  /*
  robot.go(60);
  delay(1);
  */





}
