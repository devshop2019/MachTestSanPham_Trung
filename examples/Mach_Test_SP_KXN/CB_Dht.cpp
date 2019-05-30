#include "CB_Dht.h"
#include "MachTest_SP_IO.h"

DHT *dht;
//UltraSonicDistanceSensor *distanceSensor;  // Cài đặt pin Triger(output) là 5, Echo(input) là 6

Dht_Data::Dht_Data(){
  this->nameDevice = "DHT";
  this->timeInterval= 2000;
  this->valueDevice = "No device";
}

bool Dht_Data::getData() { 
//  this->valueDevice = (String)distanceSensor->measureDistanceCm();  
  if(dht){
    float h = dht->readHumidity();
    float t = dht->readTemperature();
    if(isnan(h)){
      reInit(DHT11);
      h = dht->readHumidity();
      t = dht->readTemperature();

    }else if(h < 40){
      reInit(DHT22);
      h = dht->readHumidity();
      t = dht->readTemperature();
    }

    this->valueDevice = String(t) + "    " + String(h);
  }
  
  return true;
}

bool Dht_Data::reInit(uint8_t _type){
  deInit();
  dht = new (DHT)(DHTPIN, _type);
  dht->begin();
}

bool Dht_Data::init(){
  deInit();
  dht = new (DHT)(DHTPIN, DHT11);
  dht->begin();
}

bool Dht_Data::deInit(){
  if(dht){
    delete dht;
    dht = 0;
  }
  pinMode(DHTPIN, INPUT);
  this->valueDevice = "No device";
}

Dht_Data Dht_Device;
