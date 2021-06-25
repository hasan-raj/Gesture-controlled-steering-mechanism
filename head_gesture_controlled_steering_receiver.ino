
#include <RH_ASK.h>

#include <SPI.h> 

#include"ServoTimer2.h"
ServoTimer2 servo1;
int x,y ,z;

 
 

 
String message; 
String myString;

int xvalue; 
int yvalue;
int buttonf;
int xdata; 
int ydata; 
int zdata;
 
 



 
int val;


RH_ASK rf_driver(2000,2, 4, 5); 
 
void setup()
{
    delay(1000);
  Serial.begin(9600);  

    Serial.println("setup");
 
    if (!rf_driver.init())

       {  Serial.println("init failed");}

  servo1.attach(6); 
  
 
  

     
 
}
void loop()
{
  
  
   uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = RH_ASK_MAX_MESSAGE_LEN;

    
 
    if (rf_driver.recv(buf, &buflen)) // Non-blocking
    {
    int i;
 
     
    
    
    for (i = 0; i < buflen; i++)
    {
        char c = (buf[i]);
            message = message + c ; // make a message from the received characters         
    }
  myString = message; 
    Serial.println(message);
 
String l = getValue(myString, ',', 0); // xvalue
String m = getValue(myString, ',', 1); // yvalue
String n = getValue(myString, ',', 2); // buttonf

 
xdata = l.toInt();
ydata = m.toInt();
zdata = n.toInt();
 

  if ( (zdata > 0)&&(zdata <= 40) )
 {
   Serial.println("forward"); 



 z=map(zdata,0,12,1500,750);

    servo1.write(z);  //min pulse width for 0 degree


 }

 

  if ( (zdata >= -40)&&(zdata <0) )
 {
   Serial.println("reverse");



   z=map(zdata,0,-12,1500,2250);

servo1.write(z);  //min pulse width for 0 degree
   

}

 


  message = "";
    }


}    

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex) 
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
