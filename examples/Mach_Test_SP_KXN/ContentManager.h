#ifndef _CONTENT_H_MANAGER_H__
#define _CONTENT_H_MANAGER_H__
#include "arduino.h"
#include <LiquidCrystal_I2C.h>
#include "Sieu_Am.h"
#include "CB_Dht.h"

/*--------------------------------User define------------------------------*/
enum{
  SIEU_AM_DEVICE_ID=0,
  DHT_DEVICE_ID,
  LAST_ID_DEVICE
};
/*================================End user define==========================*/

extern Data_Adapter *listDevide[LAST_ID_DEVICE];

extern byte Choseen_Menu; // Cài đặt số Menu lựa chọn loại Module
extern unsigned long Current_Millis;
extern LiquidCrystal_I2C lcd;

extern void Test_SP2();
extern void Test_Choseen_Menu2();
extern void initContentManager();
extern void deInitContentManager();
#endif
