#include "Sieu_Am.h"
#include "MachTest_SP_IO.h"

UltraSonicDistanceSensor *distanceSensor;  // Cài đặt pin Triger(output) là 5, Echo(input) là 6

SieuAm_Data::SieuAm_Data(){
  this->nameDevice = "Sieu Am";
  this->timeInterval=250;
  this->valueDevice = "No device";
}

bool SieuAm_Data::getData() { 
  this->valueDevice = (String)distanceSensor->measureDistanceCm();  
  
  return true;
}

bool SieuAm_Data::init(){
  distanceSensor = new (UltraSonicDistanceSensor)(TRIG_PIN, ECHO_PIN);
}

bool SieuAm_Data::deInit(){
  delete distanceSensor;
  pinMode(TRIG_PIN, INPUT);
  pinMode(TRIG_PIN, ECHO_PIN);
}

SieuAm_Data sieuAm_Device;
