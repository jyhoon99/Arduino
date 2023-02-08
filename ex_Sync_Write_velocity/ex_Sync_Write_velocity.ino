
#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  115200
#define DXL_ID_1    3
#define DXL_ID_2    5

DynamixelWorkbench dxl_wb;

uint8_t dxl_id[2] = {DXL_ID_1, DXL_ID_2};
uint16_t model_number = 0;
const uint8_t handler_index = 0;
int32_t goal_speed = 100;


void setup() {
  Serial.begin(57600);

  const char *log;
  bool result = false;

//init
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

  for (int cnt = 0; cnt < 3; cnt++)
  {
    
    //ping
    result = dxl_wb.ping(dxl_id[cnt], &model_number, &log);
    if (result == false)
    {
      Serial.println(log);
      Serial.println("Failed to ping");
    }
    else
    {
      Serial.println("Succeeded to ping");
      Serial.print("id : ");
      Serial.print(dxl_id[cnt]);
      Serial.print(" model_number : ");
      Serial.println(model_number);
    }

    //wheel mode
    result = dxl_wb.wheelMode(dxl_id[cnt], 0, &log);
    if (result == false)
    {
      Serial.println(log);
      Serial.println("Failed to change wheel mode");
    }
    else
    {
      Serial.println("Succeed to change wheel mode");
    }
  }
  result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Velocity", &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to add sync write handler");
  }
}

void loop() {
  const char *log;
  bool result = false;
  result = dxl_wb.syncWrite(handler_index, &goal_speed, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to sync write position");
  }

  delay(3000);
  
}
