#ifndef _DATA_H_ADAPTER_H_
#define _DATA_H_ADAPTER_H_

#include "arduino.h"

class Data_Adapter{
  public:
  
  Data_Adapter(){};
  virtual ~Data_Adapter(){};
  
  unsigned long timeInterval;
  String nameDevice;
  String valueDevice;

  virtual bool getData(){};
  virtual bool init(){};
  virtual bool deInit(){};
   
};

#endif
