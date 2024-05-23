/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined L298_MOTOR_DRIVER
  void initMotorController() {
    digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
  }
  
  void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;
  
    if (spd < 0)
    {
      spd = -spd;
      reverse = 1;
    }
    if (spd > 255)
      spd = 255;
    
    if (i == LEFT) { 
      if      (reverse == 0) { analogWrite(LEFT_MOTOR_FORWARD, spd); analogWrite(LEFT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(LEFT_MOTOR_BACKWARD, spd); analogWrite(LEFT_MOTOR_FORWARD, 0); }
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      if      (reverse == 0) { analogWrite(RIGHT_MOTOR_FORWARD, spd); analogWrite(RIGHT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(RIGHT_MOTOR_BACKWARD, spd); analogWrite(RIGHT_MOTOR_FORWARD, 0); }
    }
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined SABERTOOTH_DRIVER
  void initMotorController() {
    left_motor.attach(LEFT_MOTOR);
    right_motor.attach(RIGHT_MOTOR);

    left_motor.writeMicroseconds(LEFT_MOTOR_NEUTRAL);
    right_motor.writeMicroseconds(RIGHT_MOTOR_NEUTRAL);
  }

  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    leftSpeed  = (leftSpeed <   250)  ? leftSpeed  :  250;
    leftSpeed  = (leftSpeed > (-250)) ? leftSpeed  : -250;
    rightSpeed = (rightSpeed<   250)  ? rightSpeed :  250;
    rightSpeed = (rightSpeed> (-250)) ? rightSpeed : -250;
    
    int leftSpeedMs = LEFT_MOTOR_NEUTRAL + 2*leftSpeed;
    int rightSpeedMs =RIGHT_MOTOR_NEUTRAL+ 2*rightSpeed;

    left_motor.writeMicroseconds(leftSpeedMs);
    right_motor.writeMicroseconds(rightSpeedMs);
  }
 
#elif defined ZILKA_PARKSIDE_MOTOR_DRIVER_V1
  void initMotorController() {
    // nastavení pinů modulu
    x9.Setup(X9_CS, X9_UD, X9_INC);
    x9_2.Setup(X9_CS_2, X9_UD_2, X9_INC_2);

    x9.JumpToStep(0);
    x9_2.JumpToStep(0);
    //x9.JumpToStep(65);
    //x9_2.JumpToStep(65);
    delay(200);

    pinMode(MOTOR1_TOGGLE_RELAY_PIN,OUTPUT); // relay pin
    pinMode(MOTOR2_TOGGLE_RELAY_PIN,OUTPUT); // relay pin
    pinMode(MOTOR1_DIR_RELAY_PIN,OUTPUT); // relay pin
    pinMode(MOTOR2_DIR_RELAY_PIN,OUTPUT); // relay pin

    digitalWrite(MOTOR1_TOGGLE_RELAY_PIN,LOW); // relay closed // TODO check
    digitalWrite(MOTOR2_TOGGLE_RELAY_PIN,HIGH); // relay closed
    
    digitalWrite(MOTOR1_DIR_RELAY_PIN,LOW); // relay closed
    digitalWrite(MOTOR2_DIR_RELAY_PIN,LOW); // relay closed
  }
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    // RC_in ma hodnoty of -1 do 1
      //motor1_speed = RC_in[1] - RC_in[0];
      //motor1_dir = motor1_speed > 0.0 ? 1 : -1;
      //motor2_speed = RC_in[1] + RC_in[0]; // second drill is turned placed opposite so opposite logic
      //motor2_dir = motor2_speed < 0.0 ? 1 : -1;

      motor1_speed = leftSpeed / 256.0;
      motor1_dir = motor1_speed > 0.0 ? 1 : -1;
      motor2_speed = rightSpeed / 256.0; // second drill is turned placed opposite so opposite logic
      motor2_dir = motor2_speed < 0.0 ? 1 : -1;

      if (motor1_dir != motor1_dir_last) // motor direction changed
      {
        x9.JumpToStep(0); // stop motor
      
        digitalWrite(MOTOR1_TOGGLE_RELAY_PIN, LOW); // disable motor
        
        motor1_dir_last = motor1_dir; // save the value for next iteration
        
        if (motor1_dir == 1) { digitalWrite(MOTOR1_DIR_RELAY_PIN, LOW); } // switch motor direction
        else                 { digitalWrite(MOTOR1_DIR_RELAY_PIN, HIGH); }
         
        delay(20);
        digitalWrite(MOTOR1_TOGGLE_RELAY_PIN, HIGH); // enable motor // TODO check this is the correct action to enable
        // TODO do the same for other motor
      }

      if (motor2_dir != motor2_dir_last) // motor direction changed
      {
        x9_2.JumpToStep(0);
        
        digitalWrite(MOTOR2_TOGGLE_RELAY_PIN, LOW); // disable motor
        
        motor2_dir_last = motor2_dir; // save the value for next iteration
        
        if (motor2_dir == 1) { digitalWrite(MOTOR2_DIR_RELAY_PIN, LOW); } // switch motor direction
        else                 { digitalWrite(MOTOR2_DIR_RELAY_PIN, HIGH); }
         
        delay(20);
        digitalWrite(MOTOR2_TOGGLE_RELAY_PIN, HIGH); // enable motor // TODO check this is the correct action to enable
        // TODO do the same for other motor
      }

      // TODO add histeresis for checking the dir so the relay doesnt switch all the time 
      //Serial.print(" motor1_speed: ");
      //Serial.print(motor1_speed*4);
      //Serial.print(" motor2_speed: ");
      //Serial.println(motor2_speed*4);
      
      motor1_speed = abs(motor1_speed);
      motor2_speed = abs(motor2_speed);
      
      motor1_speed = (motor1_speed > 1.0 ? 1.0 : motor1_speed);
      motor2_speed = (motor2_speed > 1.0 ? 1.0 : motor2_speed);
      int i_motor1_speed = (int) (motor1_speed*NUM_STEPS);
      int i_motor2_speed = (int) (motor2_speed*NUM_STEPS);

      //Serial.print(" motor1_speed: ");
      //Serial.print(motor1_speed);
      //Serial.print(" motor2_speed: ");
      //Serial.println(motor2_speed);
      if (i_motor1_speed || i_motor2_speed){
        Serial.print(" ");
        Serial.print(i_motor1_speed);
        Serial.print(" ");
        Serial.println(i_motor2_speed);  
      }
      
      x9.JumpToStep(i_motor1_speed);
      x9_2.JumpToStep(i_motor2_speed);
  } 
#else
  #error A motor driver must be selected!
#endif

#endif
