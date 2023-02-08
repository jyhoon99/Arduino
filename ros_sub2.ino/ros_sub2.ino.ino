//moving at MsgCB

#include <ros.h>
#include <geometry_msgs/Twist.h>

#include <DynamixelWorkbench.h>

#define DEVICE_NAME ""    //OPENCR            //init_param
#define BAUDRATE 115200                       //init_param
#define DXL_ID_L 3                            //param_id_index1
#define DXL_ID_R 4                            //param_id_index2

DynamixelWorkbench dxl_wb;

ros::NodeHandle nh;



void MsgCB(const geometry_msgs::Twist& msg){
//   ROS_INFO("receive: [%lf]", msg.linear.x);
// ROS_INFO("receive: [%lf]", msg.angular.z);

   const char *log;
   bool result = false;
   
   double lin_vel_step = msg.linear.x;           //goalVelocity_param    mode1
   double ang_vel_step = msg.angular.z;          //goalVelocity_param    mode2,mode3

   uint8_t dxl_id[2] = {DXL_ID_L, DXL_ID_R};    //function_param_id
   uint16_t model_number = 0;                   //ping_param_model_number
   const uint8_t handler_index = 0;             //syncWrite_param_index
   int32_t goal_speed[2] = {0, 1023};           //syncWrite_param_*data


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

  

    for (int cnt = 3; cnt < 5; cnt++)
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

    //wheelMode
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
    if (ang_vel_step == 0){
      //mode3
      dxl_wb.goalVelocity(dxl_id[cnt], int(lin_vel_step));           //mode1 or mode3
      delay(3000);    
    }
      
  }
}
//addSyncWriteHandler
  result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Speed", &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to add sync write handler");
  }
//syncWrite
   result = dxl_wb.syncWrite(handler_index, &goal_speed[0], &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to sync write speed");
  }  
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &MsgCB );

void setup() {
  // DynamixelWrokbench
    nh.initNode();
    nh.subscribe(sub);

    Serial.begin(115200);
}

void loop() {
  nh.spinOnce();
}
