//moving at setup/loop

#include <ros.h>
#include <geometry_msgs/Twist.h>

#include <DynamixelWorkbench.h>

#define DEVICE_NAME ""    //OPENCR
#define BAUDRATE 115200
#define DXL_ID_L 3
#define DXL_ID_R 4

DynamixelWorkbench dxl_wb;

ros::NodeHandle nh;



void MsgCB(const geometry_msgs::Twist& msg){
 int a = msg.linear.x;         
 int b = msg.angular.z;
 
 int vel_l;
 int vel_r;
 int theta;
 if (b ==0){           // MODE1 : foward or backward
  vel_l = vel_r = a;

 }
 else if (b > 0){
  vel_l - vel_r > 0;    //MODE2 : cw
  theta = (vel_l + vel_r)/2;
                        //MODE3 : if (vel == -vel_r) cw rotate
 }
 else if (b <0){
  vel_l - vel_r < 0;   //MODE2 : ccw
  theta = (vel_l + vel_r)/2;
                        //MODE3 : if (vel == -vel_r) ccw rotate

 }
}
ros::Subscriber<geometry_msgs::Twist> sub("topic", &MsgCB );

void setup() {
  // DynamixelWrokbench
    nh.initNode();
    nh.subscribe(sub);

    Serial.begin(115200);
}

void loop() {
   uint8_t dxl_id[2] = {DXL_ID_L, DXL_ID_R};
    uint16_t model_number = 0;

    const char *log;        
    bool result = false;    

  // Set Wheel Mode
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

    //for (int count = 0; count < 3; count++)
    //{
      dxl_wb.goalVelocity(dxl_id[cnt], (int32_t)-100);  //cw
      delay(3000);

      // dxl_wb.goalVelocity(dxl_id[cnt], (int32_t)100);  //ccw
      // delay(3000);
    //}

      //dxl_wb.goalVelocity(dxl_id[cnt], (int32_t)0);
   }
   }



  nh.spinOnce();
}
