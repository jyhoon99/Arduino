<<<<<<< HEAD
#include "sub_config.h"

//*Setup Function*
void setup() {
//Init & Setting
    nh.initNode();
    
    nh.subscribe(cmd_vel);
    
    nh.advertise(cmd_vel_cb);

    

    Serial.begin(115200);
}

//*Loof function*
void loop() {
//Send log message after ROS connection

//Receieve data cmd_vel

//Call all the callbacks waiting to be called at that point in time
  nh.spinOnce();

}

//*Callback function for sound msg*


//*Publish msgs cmd_vel

//*Update sensor
=======
//moving at MsgCB
//ver.Minhong

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Int8.h>

#include <DynamixelWorkbench.h>

#define DEVICE_NAME ""    //OPENCR            //init_param
#define BAUDRATE 115200                       //init_param
#define DXL_ID_L 3                            //param_id_index1
#define DXL_ID_R 4                            //param_id_index2

DynamixelWorkbench dxl_wb;

ros::NodeHandle nh;


   

   std_msgs::String str_msg;
   std_msgs::UInt8 uint_msg;      //uint8
   std_msgs::Int8 int_msg;        //int8
   ros::Publisher pub("topic", &str_msg);

   


void MsgCB(const geometry_msgs::Twist& msg){
//   ROS_INFO("receive: [%lf]", msg.linear.x);
//   ROS_INFO("receive: [%lf]", msg.angular.z);

   const char *log;
   bool result = false;
   
   double lin_vel_step = msg.linear.x;           //goalVelocity_param    mode1
   double ang_vel_step = msg.angular.z;          //goalVelocity_param    mode2,mode3

   uint8_t dxl_id[2] = {DXL_ID_L, DXL_ID_R};    //function_param_id
   uint16_t model_number = 0;                   //ping_param_model_number
   const uint8_t handler_index = 0;             //syncWrite_param_index
   int32_t goal_speed[2] = {0, 1023};           //syncWrite_param_*data

      ros::Publisher pub("topic", &str_msg);


   //init
  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {    
    //Serial.println(log);
    //Serial.println("Failed to init");
    str_msg.data = log;
    str_msg.data = "Failed to init";
    pub.publish( &str_msg );
  }
  else
  {
//    Serial.print("Succeeded to init : ");
//    Serial.println(BAUDRATE);  
    str_msg.data = "Succeeded to init";
//    str_msg.data= BAUDRATE; //convert string 2 int
    pub.publish( &str_msg );
  }

  

    for (int cnt = 3; cnt < 5; cnt++)
  {    
    //ping
    result = dxl_wb.ping(dxl_id[cnt], &model_number, &log);
    if (result == false)
    {
//      Serial.println(log);
//      Serial.println("Failed to ping");
      str_msg.data = log;
      str_msg.data = "Failed to ping";
      pub.publish( &str_msg );
    }
    else
    {
//      Serial.println("Succeeded to ping");
//      Serial.print("id : ");
//      Serial.print(dxl_id[cnt]);
//      Serial.print(" model_number : ");
//      Serial.println(model_number);
//      str_msg.data3 = "Succeeded to ping";
      str_msg.data = "id : ";    
//      str_msg.data = (dxl_id[cnt]);   //convert string 2 int
      str_msg.data = " model_number : ";
//      str_msg.data = (model_number);    //convert string 2 uint
      pub.publish( &str_msg );
    }

    //wheelMode
    result = dxl_wb.wheelMode(dxl_id[cnt], 0, &log);
  if (result == false)
  {
//    Serial.println(log);
//    Serial.println("Failed to change wheel mode");
    str_msg.data = log;
    str_msg.data = "Failed to change wheel mode";
    pub.publish( &str_msg );
  }
  else
  {
//    Serial.println("Succeed to change wheel mode");
//    Serial.println("Dynamixel is moving...");
    if (ang_vel_step == 0){
      //mode3
      dxl_wb.goalVelocity(dxl_id[cnt], int(lin_vel_step));           //mode1 or mode3
      delay(3000);

      str_msg.data  = ("Succeed to change wgeel mode");
      str_msg.data  = ("Dynamixel is moving...");
      //uint8, int data 
           
      pub.publish( &str_msg );
      //uint8, float data publish
    }
      
  }
}
//addSyncWriteHandler
  result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Speed", &log);
  if (result == false)
  {
//    Serial.println(log);
//    Serial.println("Failed to add sync write handler");
    str_msg.data = log;
    str_msg.data = "Failed to add sync write handler";
    pub.publish( &str_msg );

  }
//syncWrite
   result = dxl_wb.syncWrite(handler_index, &goal_speed[0], &log);
  if (result == false)
  {
//    Serial.println(log);
//    Serial.println("Failed to sync write speed");
      str_msg.data = log;
      str_msg.data = "Failed to sync write speed";
    pub.publish( &str_msg );

  }  
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &MsgCB );

void setup() {
  // DynamixelWrokbench
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(pub);

    Serial.begin(115200);
}

void loop() {
  nh.spinOnce();
}
>>>>>>> eb589720b6a8417bcfdf7295674c198b6117d1ab
