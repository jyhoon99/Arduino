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
