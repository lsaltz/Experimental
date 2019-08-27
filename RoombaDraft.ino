#include <Roomba.h>
#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"


Roomba roomba(&Serial, Roomba::Baud115200);
TMRpcm tmrpcm;
int alarmTime = 1200000;
int currentTime = 0;
int driveRadius = 300;
int backTime = 0;
int homeAngle = 180;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(100);

  roomba.start();
  Serial.begin(115200); 
  tmrpcm.speakerPin = 9;
  
  
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
}


  
  delay(100); 

  roomba.safeMode();
  delay(500);

  roomba.leds(ROOMBA_MASK_LED_PLAY, 255, 255);
  delay(1000);
  roomba.leds(ROOMBA_MASK_LED_NONE, 0, 0);
  delay(1000);

  
  uint8_t song[] = {62, 12, 66, 12, 69, 12, 74, 36};
  roomba.song(0, song, sizeof(song));
  roomba.playSong(0);
  delay(1000);
}

void GoHome(){
  roomba.start();
  roomba.drive(200, 100);
  roomba.waitAngle(homeAngle);

  for(byte i=0; i<3000; i++){
    roomba.drive(200, 0);
    roomba.waitEvent(5);
    tmrpcm.play("1.wav");
    roomba.waitEvent(6);
    tmrpcm.play("1.wav");
    roomba.waitEvent(7);
    tmrpcm.play("1.wav");
    }
    roomba.power();
  }

void loop() {

  while(currentTime < alarmTime){
   currentTime++;

  roomba.drive(200, driveRadius+=100);
  roomba.safeMode();
  roomba.waitEvent(5);
  delay(1000);
  roomba.cover();
  
  roomba.waitEvent(6);
  delay(100);
  tmrpcm.play("1.wav");
  delay(1000);

  while (backTime < 3000){
  backTime++;
  roomba.drive(-200, 0);
    }
    delay(100);
    roomba.waitAngle(345);
    delay(100);

  roomba.waitEvent(5);
  delay(100);
  tmrpcm.play("1.wav");
  delay(1000);

  while (backTime < 3000){
  backTime++;
  roomba.drive(-200, 0);
    }
    delay(100);
    roomba.waitAngle(155);
    delay(100);

    roomba.drive(200, driveRadius+=100); 
  }

  if(currentTime >= alarmTime){
    GoHome();
    }
  
}
