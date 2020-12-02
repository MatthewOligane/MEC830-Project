#include "Stepper.h"
#define STEPS  32 
#include <Servo.h>
#include <SR04.h>
#define TRIG_PIN 5
#define ECHO_PIN 3 

Servo servo;
Stepper stepper(STEPS, 8, 10, 9, 11);
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

int distance;

int rs_value; //right sensor value

int ls_value; //left sensor value

int i; //counter

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(1000);
  servo.attach(6);
  servo.write(90);
}

void loop(){
  distance=sr04.Distance();
  Serial.println(distance);
  if(distance < 8) //detects an obstacle in 10cm (arbitrary distance, should be ~L)
  {
    if(i > 1)
    {
      stepper.step(0);
      delay(10000);
    }
    Serial.println("Osbtacle Detected");
    obstacle();
  }
  servo.write(97);
  stepper.step(300);

}

void obstacle(){
  servo.write(135); //turn driver wheel right
  delay(500);
  stepper.step(2250); //rotate right
  delay(1500);
  servo.write(97);
  stepper.step(3500); //drive forward
  servo.write(45); //turn driver wheel left
  delay(500);
  stepper.step(3500); //rotate left
  delay(1500);
  servo.write(97);
  delay(500);
  stepper.step(4500); //drive forward
  delay(500);
  servo.write(135);
  stepper.step(2000); //rotate right
  delay(1500);
  servo.write(97);
  i = 2;
}
