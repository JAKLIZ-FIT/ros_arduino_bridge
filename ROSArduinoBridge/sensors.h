/* Functions for various sensor types */

float microsecondsToCm(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per cm.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

long Ping(int pin) {
  long duration, range;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);

  // convert the time into meters
  range = microsecondsToCm(duration);
  
  return(range);
}
#ifdef USE_MAG
  // libraries for magnetometer
  #include <Wire.h>
  #include <Adafruit_Sensor.h>
  #include <Adafruit_HMC5883_U.h> 

  // give random id
  Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

  int setup_mag(void);
  float read_mag(void);
#endif

// front bumper with two limit switches
#ifdef FRONT_BUMPER // for sabertooth safety pin, connect limit switches in series
  #define LEFT_F_BUMPER_PIN PD7
  #define RIGHT_F_BUMPER_PIN PD8
#endif // FRONT_BUMPER
