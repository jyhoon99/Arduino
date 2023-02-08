
//headfile
#include <ros.h>
#include <geometry_msgs/Twist.h>
//#include <std_msgs/String.h>
//#include <std_msgs/UInt8.h>
//#include <std_msgs/Int8.h>

#include <DynamixelWorkbench.h>
#include "MX_msg.h"

//set parameter
#define DEVICE_NAME ""    //OPENCR            //init_param
#define BAUDRATE 115200                       //init_param
#define DXL_ID_L 3                            //param_id_index1
#define DXL_ID_R 5                            //param_id_index2

DynamixelWorkbench dxl_wb;

ros::NodeHandle nh;

//
//*Publisher
//

std_msgs::String str_msg;
ros::Publisher pub("topic", &str_msg);


std_msgs::UInt8 uint_msg;      //uint8
std_msgs::Int8 int_msg;        //int8


void MsgCB(const geometry_msgs::Twist& msg);
