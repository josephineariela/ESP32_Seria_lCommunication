/*
 * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * 
*/
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();
HardwareSerial MySerial(1);
 
#define RXD2 16
#define TXD2 17

String tS, hS;

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  MySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //Serial.println("Serial Txd is on pin: "+String(TX));
  //Serial.println("Serial Rxd is on pin: "+String(RX));

  if (! sht31.begin(0x44)){
    Serial.println("Couldn't find SHT31");
    while (1) 
      delay(1);
  }
  
}
 
void loop() { //Choose Serial1 or Serial2 as required

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  tS = String(t);
  hS = String(h);
  
  MySerial.println("Sending New Data...x");
  Serial.println("Sending New Data...");
//  MySerial.println("27.03y");
//  MySerial.println("80.55z");
  if (! isnan(t)){
    MySerial.println(tS + "y");
    Serial.println("ActTemp = " + tS);
  }
  else{
    //MySerial.println("Failed to read temperature");
    Serial.println("Failed to re`ad temperature");
  }
  if (! isnan(h)){
    MySerial.print(hS + "z");
    Serial.print("ActHum = " + hS);
  }
  else{
    Serial.println("Failed to read humidity");
  }
  MySerial.println();
  Serial.println("Data Sent..");
  delay(5000);
  
}
