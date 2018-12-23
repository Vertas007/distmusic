#include <L298N.h>

#define enA 10
#define in1 9
#define in2 8

#define enB 5
#define in3 7
#define in4 6

//create a motor instance
L298N motor(enA, in1, in2);

void setup() {

  //used for display information
  Serial.begin(9600);
}

void Accelerate() {
  motor.forward();
  
  for(int i=0;i<256;i++)
  {
    motor.setSpeed(i);
    delay(30);
  }
}

void Decelerate() {
  motor.forward();
  
  for(int i=255;i>=0;i--)
  {
    motor.setSpeed(i);
    delay(30);
  }
}

void loop() {
  Accelerate();
  Decelerate();
}
