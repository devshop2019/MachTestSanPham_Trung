#include "ContentManager.h"

Data_Adapter *listDevide[LAST_ID_DEVICE] = {
                                              &Dht_Device,
                                              &sieuAm_Device,
                                           };

unsigned long contentManager_TimeInterval;

void Test_SP2()
{
    if(millis() - Current_Millis > contentManager_TimeInterval )  // Sau mỗi 0.25s mới cập nhập
    {
      Current_Millis = millis();
      if(listDevide[Choseen_Menu])
      listDevide[Choseen_Menu]->getData();
      //
      lcd.clear();            // Xóa màn hình
      lcd.setCursor(2,0);     // Cột 2 dòng 0
      lcd.print(listDevide[Choseen_Menu]->nameDevice);
      lcd.setCursor(2,1);     // Cột 2 dòng 0
      lcd.print(listDevide[Choseen_Menu]->valueDevice);
      contentManager_TimeInterval = listDevide[Choseen_Menu]->timeInterval;
    }
}

void Test_Choseen_Menu2() /* Có các mục menu 1 - 2 - 3 - 4*/
{
  if(Choseen_Menu >= LAST_ID_DEVICE) {Choseen_Menu = 0;}
  if(Choseen_Menu <0) {Choseen_Menu = LAST_ID_DEVICE-1;}
}

void initContentManager(){
  if(listDevide[Choseen_Menu])
  listDevide[Choseen_Menu]->init();
}

void deInitContentManager(){
  if(listDevide[Choseen_Menu])
  listDevide[Choseen_Menu]->deInit();
}

