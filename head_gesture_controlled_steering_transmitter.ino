#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

#include <RH_ASK.h>

#include <SPI.h> 



RH_ASK rf_driver(2000,4, 2, 5); 
 
 String str;
 char cstr[100];
String message = "";
unsigned int mlength; 
 

 
 int xdata = 0; 
 int ydata = 0;
 int zdata = 0; 
 
void setup()
{
     Serial.begin(9600);  

      if(!accel.begin())
   {
      Serial.println("No valid sensor found");
      while(1);
   } 

      if (!rf_driver.init())

   {   
    Serial.println("init failed");
   }
 
  
  

  

}



 
void loop()
{

  sensors_event_t event; 
   accel.getEvent(&event);
//   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
//   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
//   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
   

  int zpos=0,xpos=0,ypos=0;
  int x=event.acceleration.x ;
  int y=event.acceleration.z;
  int z=event.acceleration.y;
  int sensitivity=20;    
  if(x>=0)                    
  xpos=map(x,0,20,0,sensitivity); 
  if(x<=0)                   
  xpos=map(x,0,-20,0,-sensitivity);   
  if(y>=0)                   
  ypos=map(y,0,20,0,-sensitivity);  
  if(y<=0)                 
  ypos=map(y,0,-20,0,sensitivity); 
 

  if(z>=0)                    
  zpos=map(z,0,20,0,-sensitivity);  
  if(z<=0)                  
  zpos=map(z,0,-20,0,sensitivity); 
  
 
  if(xpos!=0 or ypos!=0) 
  {
   xdata=xpos;
  ydata=ypos;
  zdata=zpos;
  Serial.print(xdata);    
  Serial.print(":");
  Serial.print(ydata);
  Serial.print(":");
  Serial.println(zdata);

  
  SendData(xdata,ydata,zdata); 
  delay(100);
  }
  

                
}
 

void SendData( int xvalue,int yvalue,int buttonstatus)
{

 
message = message + xvalue +"," + yvalue + "," + buttonstatus ;
mlength = message.length(); // find the number of characters in a message.
  str = message;
  str.toCharArray(cstr,100);
  rf_driver.send((uint8_t *)cstr, mlength);
  rf_driver.waitPacketSent(); // Wait until the whole message is gone
  str = "";
  message = ""; 



}
 
 
