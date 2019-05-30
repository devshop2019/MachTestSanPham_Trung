#ifndef _DHT_H_H__
#define _DHT_H_H__

#include "dataAdapter.h"
#include "DHT.h"

extern DHT *dht;
//extern UltraSonicDistanceSensor * distanceSensor;

class Dht_Data: public Data_Adapter{
  public:
  Dht_Data();
  bool getData();
  bool reInit(uint8_t _type);
  bool init();
  bool deInit();
};

extern Dht_Data Dht_Device;

#endif
