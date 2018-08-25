//www.elegoo.com
//2016.12.08
//
#include "SR04.h"
#include <Tone.h>

#define TRIG_PIN 12
#define ECHO_PIN 11
#define BUTTON_PIN 2

#define BUZZER_PIN0 8
#define BUZZER_PIN1 9

#define LED0_PIN 3
#define LED1_PIN 4
#define LED2_PIN 5

#define ANALOG_PIN A0

// Töne
Tone prime;
Tone terzDur;
Tone quint;
// end Töne

// Distanzmessung
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;
// end Distanzmessung

int dMin = 5;
int dMax = 40;

//int fMin1 = 262; // C4
//int fMax1 = 523; //C5
int fMin1 = 523; //C5
int fMax1 = 262; // C4
float m1 = float(fMax1 - fMin1) / float(dMax - dMin);
float f1 = fMin1 - (dMin * m1);

int fMin2 = 523; // C5
int fMax2 = 1047; // C6
float m2 = float(fMax2 - fMin2) / float(dMax - dMin);
float f2 = fMin2 - (dMin * m2);

float m = m2;
float f = f2;

bool onoff = false;

int inputAnalog;
int del;


float quintFactor = 1.498307077;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED0_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  prime.begin(BUZZER_PIN0);
  quint.begin(BUZZER_PIN1);

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
      digitalWrite(LED0_PIN, HIGH);
      prime.play(262, 200);
      delay(200);
      digitalWrite(LED1_PIN, HIGH);
      prime.play(330, 200);
      delay(200);
      digitalWrite(LED2_PIN, HIGH);
      prime.play(392, 200);
      delay(200);
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
      digitalWrite(LED0_PIN, LOW);
      digitalWrite(LED1_PIN, LOW);   
    } else {
      prime.stop();
      quint.stop();
      
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
    }
  }

  inputAnalog = analogRead(ANALOG_PIN);
  //if(inputAnalog <= 50)
 // {
   // inputAnalog = 0;
  //}  
  //Serial.println(inputAnalog);
  del = map(inputAnalog, 0, 1023, 0, 50);

  //if (digitalRead(BUTTON_PIN) == LOW) {
  //  m = m1;
  //  f = f1;
  //} else {
  //  m = m2;
  //  f = f2;
  //}
  if (onoff) {
    if (a >= dMin && a <= dMax) {
      int freq = m * a + f;
      //int freqQuint = int(freq*quintFactor);
      //Serial.print(freq);
      prime.play(freq);
      //quint.play(freqQuint);
      delay(del);
    } else {
    prime.stop();
    quint.stop();
    //Serial.print(0);
    } // end else
    //Serial.print(" Hz");    
  } // end else onoff

  //Serial.println();

}
