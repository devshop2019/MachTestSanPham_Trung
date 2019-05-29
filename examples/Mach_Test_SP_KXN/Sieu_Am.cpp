#include "Sieu_Am.h"
#include "MachTest_SP_IO.h"

UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);  // Cài đặt pin Triger(output) là 5, Echo(input) là 6



SieuAm_Data::SieuAm_Data(){
  this->nameDevice = "Sieu Am";
  this->timeInterval=250;
  this->valueDevice = "No device";
}

bool SieuAm_Data::getData() {
  
  this->valueDevice = (String)distanceSensor.measureDistanceCm();  
  
  return true;
}

SieuAm_Data sieuAm_Device;
