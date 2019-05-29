#ifndef _SIEU_H_AM_H__
#define _SIEU_H_AM_H__

#include "dataAdapter.h"
#include <HCSR04.h>

extern UltraSonicDistanceSensor distanceSensor;

class SieuAm_Data: public Data_Adapter{
  public:
  SieuAm_Data();
  bool getData();
};

extern SieuAm_Data sieuAm_Device;

#endif