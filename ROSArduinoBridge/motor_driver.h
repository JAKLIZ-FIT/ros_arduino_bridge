/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD 5
  #define LEFT_MOTOR_BACKWARD  6
  #define RIGHT_MOTOR_FORWARD  9
  #define LEFT_MOTOR_FORWARD   10
  #define RIGHT_MOTOR_ENABLE 12
  #define LEFT_MOTOR_ENABLE 13
#endif

// diplomova prace
// 2 digitalni potenciometry, uno, rc, vrtacky (bez rele)
// Arduino digitální potenciometr X9C103S 
// navody.dratek.cz ()
#ifdef ZILKA_PARKSIDE_MOTOR_DRIVER_V1
  #include <FastX9CXXX.h>
  // pins for digital potenciometers
  #define X9_CS  3
  #define X9_INC 4
  #define X9_UD  5
  #define X9_CS_2  6
  #define X9_INC_2 8
  #define X9_UD_2  9
  // vytvoření objektu z knihovny,
  // k dispozici jsou také nastavení:
  // FastX9C102, FastX9C104 a FastX9C503  FastX9C103
  FastX9C104 x9;
  FastX9C104 x9_2;
  #define NUM_STEPS 50.0
  
  // pins for motor enable relay/transistor
  #define MOTOR1_TOGGLE_RELAY_PIN 0
  #define MOTOR2_TOGGLE_RELAY_PIN 13
  // pins for direction switching
  #define MOTOR1_DIR_RELAY_PIN A0
  #define MOTOR2_DIR_RELAY_PIN 2
  float motor1_speed = 0;
  float motor2_speed = 0; 
  int motor1_dir = 1;
  int motor2_dir = -1;  
  int motor1_dir_last = motor1_dir;
  int motor2_dir_last = motor2_dir;
#endif

#ifdef SABERTOOTH_DRIVER
  #include <Servo.h>
  #define LEFT_MOTOR 5
  #define RIGHT_MOTOR 6
  Servo left_motor;
  Servo right_motor;
  #define LEFT_MOTOR_NEUTRAL 1500
  #define RIGHT_MOTOR_NEUTRAL 1500
  
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
