/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PD2  //pin 2
  #define LEFT_ENC_PIN_B PD3  //pin 3
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A PC0 //PC4  //pin A4
  #define RIGHT_ENC_PIN_B PC1 //PC5   //pin A5

  // changed to these pins to avoid collision with motor control
  //#define LEFT_ENC_PIN_A PD0  //pin 0
  //#define LEFT_ENC_PIN_B PD1  //pin 1
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

