# MachTestSanPham_Trung

##Cách add thêm cảm biến/module cần test vào chương trình

###1. Tạo thêm 2 file `xyz.h` và `xyz.cpp`
- Với `xyz` là tên của CB/Module cần thêm vào, ví dụ: `Sieu_Am.h`, `Sieu_Am.cpp`
- File `.h` dùng để giới thiệu cho các file khác biết các `method, class, function` đang có.
- File `.cpp` dùng để thực thi các `method, class, function` đã được khai báo trong file `.h`

####a. Viết class của CB/Module vào trong 2 file vừa tạo (`xyz.h`, `xyz.cpp`) vói tên class là: `xyz_Data`, ví dụ: với xyz là `SieuAm`

```c++
// filename: Sieu_Am.h

#ifndef _SIEU_H_AM_H__
#define _SIEU_H_AM_H__

#include "dataAdapter.h"
#include <HCSR04.h>  

extern UltraSonicDistanceSensor * distanceSensor;

class SieuAm_Data: public Data_Adapter{
  public:
  SieuAm_Data();
  virtual ~SieuAm_Data(){};
  bool getData();
  bool init();
  bool deInit();
};

extern SieuAm_Data sieuAm_Device;

#endif
```
####b. Giải thích:
```c++
#ifndef _SIEU_H_AM_H__
#define _SIEU_H_AM_H__
```
Đoạn define này đảm bảo file này chỉ được khai báo duy nhất 1 lần, tránh hiện tượng trùng lặp file.

----

Trong example của `HCSR04.h`, cảm biến sẽ được khai báo trực tiếp:

```c++
UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);
```

Cảm biến sẽ được khai báo tại file thực thi `Sieu_Am.cpp` đưới dạng con trỏ

```c++
UltraSonicDistanceSensor * distanceSensor;
```

trong file `Sieu_Am.h` ta sẽ khai báo thêm `extern` để cho các file khác biết là biến này đã được khai báo ở đâu đó ^^.

```c++
extern UltraSonicDistanceSensor * distanceSensor;
```

----

Do class `SieuAm_Data` kế thừa từ class cha `Data_Adapter`, nên thừa kế được các biến:
 - `timeInterval` : Thời gian giữa 2 lần đọc cảm biến.
 - `nameDevice`: Tên của cảm biến
 - `valueDevice`:Giá trị trả về của cảm biến.

 và các biến trên sẽ được khai báo trong `constructor` file `Sieu_Am.cpp`:
 ```c++
 SieuAm_Data::SieuAm_Data(){
    this->nameDevice = "Sieu Am";
    this->timeInterval=250;
    this->valueDevice = "No device";
}
 ```
 tuy nhiên với các method này cần phải viết lại:
  - `bool init()`: Khởi tạo cảm biến.
  - `bool getData()`: Lấy giá trị cảm biên chuyển thành chuỗi rồi xuất ra `valueDevice`.
  - `bool deInit()`: Xóa bộ nhớ `RAM`, và RESET chân của cảm biến về `INPUT`.
  
  

----

```c++
bool SieuAm_Data::init(){
    deInit();
    distanceSensor = new (UltraSonicDistanceSensor)(TRIG_PIN, ECHO_PIN);
}
```
- `deInit()`: dùng để dảm bảo là cảm biến chỉ 1 lần chiếm bộ nhớ trên `RAM`.
- Toán tử `new`: dùng để cấp phát `RAM` cho cảm biến. 
- `TRIG_PIN`, `ECHO_PIN` là 2 chân đã được định nghĩa trong file quản lý I/O `"MachTest_SP_IO.h"`, lưu ý để tránh các trường hợp khai báo trùng, nhầm chân với cảm biến khác.

```c++
//Filename: MachTest_SP_IO.h
#ifndef MACH_TEST_H_SP_IO_H__
#define MACH_TEST_H_SP_IO_H__

// Chan Chuan
#define PIN_1                   5
#define PIN_2                   6
#define PIN_3                   A4
#define PIN_4                   A5

//sieu am pin out
#define TRIG_PIN                PIN_1
#define ECHO_PIN                PIN_2
```

----

```c++
bool SieuAm_Data::getData() { 
    if(distanceSensor){
        debug_sieuam(F("doc SIeu am \r\n"));
        this->valueDevice = (String)distanceSensor->measureDistanceCm();  
    }
    return true;
}
```
 - `if(distanceSensor)` điều kiện là cảm biến đã được `init()` thì mới đọc giá trị.
 - Trong chương trình mẫu sẽ thấy là: `distanceSensor.measureDistanceCm()`.

 ----

```c++
 bool SieuAm_Data::deInit(){
    pinMode(TRIG_PIN, INPUT);
    //  pinMode(ECHO_PIN, INPUT);
    this->valueDevice = "No device";
    if(distanceSensor){
        delete distanceSensor;
        distanceSensor = 0;
    }
    debug_sieuam(F("Xoa SIeu am \r\n"));
}
```
 - Hàm này chủ yếu giải phóng `RAM` để đọc cảm biến khác, đồng thời reset chân đang sử dụng thành `INPUT`.

 ----

 ```c++
 SieuAm_Data sieuAm_Device;
 ```
 - `sieuAm_Device` cần được khai báo để add vào danh sách cảm biến
```c++
//filename: Sieu_Am.h
extern SieuAm_Data sieuAm_Device;
```

----

###2. Add cảm biến vừa tạo vào chương trình chính.

```c+
#ifndef _CONTENT_H_MANAGER_H__
#define _CONTENT_H_MANAGER_H__
#include "Sieu_Am.h"
#include "CB_Dht.h"

/*--------------------------------User define------------------------------*/
enum{
  SIEU_AM_DEVICE_ID=0,
  DHT_DEVICE_ID,
  LAST_ID_DEVICE
};
/*================================End user define==========================*/
```
 - Đoạn chương trình trên chỉ khai báo để biết số lượng các loại cảm biến có thể test. Nhớ phải `include` thư viện vừa tạo nhé (`#include "Sieu_Am.h"`).

```c++
//filename: ContentManager.cpp
  #include "ContentManager.h"

Data_Adapter *listDevide[LAST_ID_DEVICE] = {
                                              &Dht_Device,
                                              &sieuAm_Device,
                                           };
```
 - Add thêm `&sieuAm_Device` vào danh sách `listDevide`