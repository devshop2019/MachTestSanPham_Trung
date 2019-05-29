#include "Sieu_Am.h"
#include "debugkxn.h"
#include "ContentManager.h"


#include <LiquidCrystal_I2C.h>

//#include "DHT.h"

#include "button.h"

byte Choseen_Menu = 0; // Cài đặt số Menu lựa chọn loại Module
unsigned long Current_Millis = millis();
/* Cài đặt nút bấm */
button Start(2);  // Cài đặt pin nút nhấn Start là pin 2
button Up(3);     // Cài đặt pin nút nhấn Up là pin 3
button Down(4);   // Cài đặt pin nút nhấn Down là pin 4
/* Cài đặt màn hình LCD */
LiquidCrystal_I2C lcd(0x27,16,2);   // Cài đặt địa chỉ 0x27, hiển thị 16 cột 2 dòng
/* Cài */
//DHT dht_11(DHT11, 9);
//DHT dht_11(DHT11, 9);
//DHT dht_11(DHT11, 9);

// ---------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  debug("Start!");
  //
  //Start.button_1ClickHold
  Start.button_1Click = &Start_do_1_Click;
  Start.button_2Click = &Start_do_2_Click;
  //
  Up.button_1ClickHold = &Up_do_0_Click;
  Up.button_1Click = &Up_do_1_Click;
  //Up.button_2Click
  //
  Down.button_1ClickHold = &Down_do_0_Click;
  Down.button_1Click = &Down_do_1_Click;
  //Down.button_2Click
  //
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
  Start.loop(); // Xử lý nút Start
  Up.loop();    // Xử lý nút Up
  Down.loop();  // Xử lý nút Down
  //
//  Test_Choseen_Menu();  // Hàm kiểm tra mục Menu có hợp lệ không
  Test_Choseen_Menu2();
//  Test_SP();            // Hàm chọn mục SP để test
  Test_SP2();
}
// ---------------------------------------------------------------------------------------

// Hàm cho nút nhấn Start
void Start_do_1_Click()
{
  debugln("1 Click: Do it!");
}
void Start_do_2_Click()
{
  debugln("2 Click: Re Start!");
}

// Hàm cho nút nhấn Up
void Up_do_0_Click()
{
  Choseen_Menu++;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
}
void Up_do_1_Click()
{
  Choseen_Menu++;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
}

// Hàm cho nút nhấn Down
void Down_do_0_Click()
{
  Choseen_Menu--;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
}
void Down_do_1_Click()
{
  Choseen_Menu--;
  debug("1 Click: Menu"); debugln(Choseen_Menu);
}

// ---------------------------------------------------------------------------------------
void Test_Choseen_Menu() /* Có các mục menu 1 - 2 - 3 - 4*/
{
  /*
   * 1. Siêu âm   HCSR04 (Vcc - Trig - Echo - Gnd)  HCSR05 (Vcc - Trig - Echo - OUT - Gnd)    US-015 (Vcc - Trig - Echo - Gnd)
   *              |_ cái vuông                      |_ cái vuông                              |_ cái vuông
   * 2. Độ ẩm     DHT22 (Vcc - Data - NC - Gnd)     Module-DHT22 (Vcc - OUT - Gnd)            DHT11(Vcc - Data - NC - Gnd)        Module-DHT11 (Vcc - OUT - Gnd)    AM2301 ()
   *              |_ cái tròn                       |_ cái vuông                              |_ cái tròn                         |_ cái vuông
   * 3. 
   * 4. 
   */
  if(Choseen_Menu >4) {Choseen_Menu = 1;}
  if(Choseen_Menu <0) {Choseen_Menu = 4;}
}

void Test_SP()
{
  if(Choseen_Menu == 1) /* Đo Cảm biến SIÊU ÂM HCSR04 + HCSR05 + US-015 */
  {
    if(millis() - Current_Millis > 250)  // Sau mỗi 0.25s mới cập nhập
    {
      Current_Millis = millis();
      //
      lcd.clear();            // Xóa màn hình
      lcd.setCursor(2,0);     // Cột 2 dòng 0
      lcd.print("CB SIEU AM");
      lcd.setCursor(2,1);     // Cột 2 dòng 0
      lcd.print(distanceSensor.measureDistanceCm());
      lcd.print(" cm");
    }
  }
  if(Choseen_Menu == 2) /* Đo Cảm biến ĐỘ ẨM DHT11 + Module-DHT11 + DHT22 + Module-DHT22 */
  {
    if(millis() - Current_Millis > 500)  // Sau mỗi 2.1s mới cập nhập - Tần số lấy mẫu tối đa 0.5Hz
    {
      Current_Millis = millis();
      //
      lcd.clear();            // Xóa màn hình
      lcd.setCursor(2,0);     // Cột 2 dòng 0
      lcd.print("Menu 2");
      lcd.setCursor(2,1);     // Cột 2 dòng 0
      lcd.print("---");
    }
  }
  if(Choseen_Menu == 3)
  {
    if(millis() - Current_Millis > 500)  // Sau mỗi 0.5s mới cập nhập
    {
      Current_Millis = millis();
      //
      lcd.clear();            // Xóa màn hình
      lcd.setCursor(2,0);     // Cột 2 dòng 0
      lcd.print("Menu 3");
      lcd.setCursor(2,1);     // Cột 2 dòng 0
      lcd.print("---");
    }
  }
  if(Choseen_Menu == 4)
  {
    if(millis() - Current_Millis > 500)  // Sau mỗi 0.5s mới cập nhập
    {
      Current_Millis = millis();
      //
      lcd.clear();            // Xóa màn hình
      lcd.setCursor(2,0);     // Cột 2 dòng 0
      lcd.print("Menu 4");
      lcd.setCursor(2,1);     // Cột 2 dòng 0
      lcd.print("---");
    }
  }
}

