
#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  115200
#define DXL_ID_1    3
#define DXL_ID_2    4

DynamixelWorkbench dxl_wb;

void setup() 
{
  Serial.begin(57600);
  // while(!Serial); // Wait for Opening Serial Monitor

  const char *log;
  bool result = false;

  uint8_t dxl_id[2] = {DXL_ID_1, DXL_ID_2};
  uint16_t model_number = 0;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);  
  }


 for (int cnt = 3; cnt < 5; cnt++)
 {
  result = dxl_wb.wheelMode(dxl_id[cnt], 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }
  else
  {
    Serial.println("Succeed to change wheel mode");
    Serial.println("Dynamixel is moving...");

//    for (int count = 0; count < 3; count++)
//    {
      dxl_wb.goalVelocity(dxl_id[cnt], (int32_t)-500);           //cw
      delay(3000);
     

//      dxl_wb.goalVelocity(dxl_id, (int32_t)100);         //ccw
//      delay(3000);
//    }

//    dxl_wb.goalVelocity(dxl_id, (int32_t)0);            /stop
  }
 }
}

void loop() 
{

}
