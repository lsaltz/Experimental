#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 10
#define trigpin1 3
#define echopin1 2
#define trigpin2 7
#define echopin2 8

long duration, distance, RightSensor,BackSensor,FrontSensor;
TMRpcm tmrpcm;

void setup() {
  Serial.begin (9600);

  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);

  pinMode(trigpin2, OUTPUT);
  pinMode(echopin2, INPUT);

  tmrpcm.speakerPin = 9;
  
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
}

void loop() {
  SonarSensor(trigpin1, echopin1);
  FrontSensor = distance;

  SonarSensor(trigpin2, echopin2);
  BackSensor = distance;


  if (distance <=5){
    tmrpcm.setVolume(6);
    tmrpcm.play("1.wav");
    delay(5000);
  }
}

void SonarSensor(int trigpin,int echopin)
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = (duration/2) / 29.1;
}
