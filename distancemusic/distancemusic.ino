// Geile Mukke by Chris&Matt
#include "SR04.h"
#include <Tone.h>


#define ANALOG_PIN A0
#define TRIG_PIN 12
#define ECHO_PIN 11
#define BUTTON_PIN 2

#define BUTTON_UP_PIN 6
#define BUTTON_DOWN_PIN 7

#define BUZZER_PIN0 8
#define BUZZER_PIN1 9

#define LED0_PIN 3
#define LED1_PIN 4
#define LED2_PIN 5

// Töne
Tone prime;
Tone other;
// end Töne

// Distanzmessung
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;
// end Distanzmessung

int dMin = 5;
int dMax = 60;

int fMinBase = 262;
int fMaxBase = 523;
float m = float(fMaxBase - fMinBase) / float(dMax - dMin);
float f = fMinBase - (dMin * m);

int oct = 4;

float littleTerzFactor = 1.189207115;
float bigTerzFactor = 1.25992105;
float quintFactor = 1.498307077;


//int fMin1 = 262; // C4
//int fMax1 = 523; //C5
//int fMin1 = 523; //C5
//int fMax1 = 262; // C4

//float m1 = float(fMax1 - fMin1) / float(dMax - dMin);
//float f1 = fMin1 - (dMin * m1);

//int fMin2 = 523; // C5
//int fMax2 = 1047; // C6
//float m2 = float(fMax2 - fMin2) / float(dMax - dMin);
//float f2 = fMin2 - (dMin * m2);

//float m = m1;
//float f = f1;

bool onoff = false;

int inputAnalog;
int del;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(LED0_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED0_PIN, HIGH);

  prime.begin(BUZZER_PIN0);
  other.begin(BUZZER_PIN1);

  //Serial.begin(9600);
  /*  Serial.print(m1);
    Serial.print(" ");
    Serial.println(m2);
    //delay(1000);*/
}

void loop() {
  a = sr04.Distance();
  //Serial.print(a);
  //Serial.print("cm - ");

  if (digitalRead(BUTTON_PIN) == LOW) {
    //delay(500);
    onoff = !onoff;

    if (onoff) {
      startUp();         
    } else {
      shutDown();     
    }
  }

  inputAnalog = analogRead(ANALOG_PIN);
  //if(inputAnalog <= 50)
 // {
   // inputAnalog = 0;
  //}  
  //Serial.println(inputAnalog);
  del = map(inputAnalog, 0, 1023, 0, 50);
  
  if (onoff) {
    if(digitalRead(BUTTON_DOWN_PIN) == LOW){
      if(oct > 2){
        prime.stop();
        other.stop();
        oct -= 1;
        int fMin = pow(2, 12*(oct-4)/12) * fMinBase;
        int fMax = pow(2, 12*(oct-4)/12) * fMaxBase;
        m = float(fMax - fMin) / float(dMax - dMin);
        f = fMin - (dMin * m);
        prime.play(fMax, 400);
        delay(200);
        other.play(fMin, 200);
      }
      delay(250);
    }
    if(digitalRead(BUTTON_UP_PIN) == LOW){
      if(oct < 8){
        prime.stop();
        other.stop();
        oct += 1;
        int fMin = pow(2, 12*(oct-4)/12) * fMinBase;
        int fMax = pow(2, 12*(oct-4)/12) * fMaxBase;
        m = float(fMax - fMin) / float(dMax - dMin);
        f = fMin - (dMin * m);
        prime.play(fMin, 400);
        delay(200);
        other.play(fMax, 200);
      }
      delay(250);
    }
    
    if (a >= dMin && a <= dMax) {
      int freq = m * a + f;
      int freqQuint = int(freq*quintFactor);
      //Serial.print(freq);

      if(del>5){
        prime.stop();
        other.stop();
        delay(del);
      }
      prime.play(freq);
      other.play(freqQuint);
    } else {
    prime.stop();
    other.stop();
    //Serial.print(0);
    } // end else
    //Serial.print(" Hz");    
  } // end else onoff

  //Serial.println();

}

void startUp(){
  for(int i = 0; i < 5; i++){
    digitalWrite(LED0_PIN, HIGH);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH); 
    delay(100);
    digitalWrite(LED0_PIN, LOW);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW); 
    delay(100);        
  }
  digitalWrite(LED0_PIN, HIGH);
  prime.play(262, 200);
  delay(200);
  digitalWrite(LED1_PIN, HIGH);
  prime.play(330, 200);
  delay(200);
  digitalWrite(LED2_PIN, HIGH);
  prime.play(392, 200);
  delay(200);
  digitalWrite(LED0_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
}

void shutDown(){
  prime.stop();
  other.stop();
      
  digitalWrite(LED0_PIN, HIGH);
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  for(int i = 0; i < 5; i++){
    digitalWrite(LED0_PIN, LOW);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW); 
    delay(100);
    digitalWrite(LED0_PIN, HIGH);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH); 
    delay(100);
    }
  digitalWrite(LED2_PIN, LOW);
  prime.play(392, 200);
  delay(200);
  digitalWrite(LED1_PIN, LOW);
  prime.play(330, 200);
  delay(200);
  digitalWrite(LED0_PIN, LOW);
  prime.play(262, 200);
  delay(200);
  digitalWrite(LED0_PIN, HIGH);
}
