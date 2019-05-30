#include "Sieu_Am.h"
#include "debugkxn.h"
#include "ContentManager.h"
#include "Btn_Process.h"
#include <LiquidCrystal_I2C.h>

/* Cài đặt màn hình LCD */
LiquidCrystal_I2C lcd(0x27,16,2);   // Cài đặt địa chỉ 0x27, hiển thị 16 cột 2 dòng

// ---------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  buttonInit();  
  debug("Start!");

  lcd.init();             // Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  lcd.backlight();        // Bật đèn nền
  lcd.clear();            // Xóa màn hình
  lcd.setCursor(3,0);     // Cột 3 dòng 0
  lcd.print("TrungKuro");
  lcd.setCursor(1,1);     // Cột 1 dòng 0
  lcd.print("Hello yours");
}
void loop() 
{
  // Down.loop();  // Xử lý nút
  buttonLoop();
  
  Test_Choseen_Menu2();
  Test_SP2();
  runSerialLife();
}
// ---------------------------------------------------------------------------------------

// Hàm cho nút nhấn Start
void Start_do_1_Click()
{
  debugln("1 Click: Do it!");
  initContentManager();
  contentManager_TimeInterval = 0;
}
void Start_do_2_Click()
{
  debugln("2 Click: Re Start!");
  deInitContentManager();
  contentManager_TimeInterval = 0;
}

// Hàm cho nút nhấn Up
void Up_do_0_Click()
{
  deInitContentManager();
  Choseen_Menu++;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
  contentManager_TimeInterval = 0;
}
void Up_do_1_Click()
{
  deInitContentManager();
  Choseen_Menu++;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
  contentManager_TimeInterval = 0;
}

// Hàm cho nút nhấn Down
void Down_do_0_Click()
{ 
  deInitContentManager();
  Choseen_Menu--;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
  contentManager_TimeInterval = 0;
}
void Down_do_1_Click()
{
  deInitContentManager();
  Choseen_Menu--;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
  contentManager_TimeInterval = 0;
}

unsigned long timeSeriallife = millis();

void runSerialLife(){
  if(millis() - timeSeriallife >= 1000){
      timeSeriallife = millis();
      Serial.println("I live!");
  }
}
