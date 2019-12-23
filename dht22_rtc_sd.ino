#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
#include <dht.h>

dht DHT;
#define DHT22_PIN 6
const int chipSelect = SS1;
RTC_DS3231 rtc;

void setup() {
Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
    DateTime now = rtc.now();
    int chk = DHT.read22(DHT22_PIN);
    float temperatura = (DHT.temperature);
    float humedad = (DHT.humidity);
    int segundo = (now.second());
    int minuto = (now.minute());
    int hora = (now.hour());
    int dia = (now.day());
    int mes = (now.month());
    int anyo = (now.year());
    
    //String ss = (String) segundo;
    //Serial.print(ss);
    
    String dataString = "";
    dataString += String(dia) + "/" + String(mes) + "/" + String(anyo) + ";"
    + String(hora) + ":" + String(minuto) + ":" + String(segundo) + ";"
    + String(temperatura) + ";"
    + String(humedad);
    

    File dataFile = SD.open("datalog.txt", FILE_WRITE);
      if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the Serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
    
    delay(3000);
}
