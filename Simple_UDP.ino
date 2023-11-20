#include <WiFi.h>
#include <WiFiUdp.h>
#include <WebServer.h>


/* WiFi network name and password */

const char * ssid = "Your own router's SSID";
const char * pwd = "Your own router's Password";

const char * udpAddress = "IP Address obtained from ipconfig";  //This is an IP address of the receiver (assuming this is PC), which can be checked by using ipconfig

const int udpPort = 3333; // Actually can use any port number but recommend using higher number because lower port number is mostly taken



//create UDP instance
WiFiUDP UDP;

int uraw1[10]; // Raw data container

int datacount =0;
int nthdata = 0;



void setup() 
{
   Serial.begin(115200);

  //Connect to WiFi
  WiFi.begin(ssid, pwd);

  //Wait for connection (For testing only)
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }

  //If WiFi is connected (For testing only)
  Serial.print("Connected to:  ");
  Serial.println(ssid);
  Serial.print("IP:  ");
  Serial.println(WiFi.localIP()); //IP address of the sender

 //Start the UDP transfer and buffer
  UDP.begin(udpPort);
  
}

void loop() 
{ 
    // Testing the UDP data transfer by sending the number 1 to 1000

    if (nthdata == 1000) 
    {
      nthdata = 0;
    } 
    nthdata++; 
    uraw1[datacount] = 1000 + nthdata;

    // Fill the data container 
    // When the data container is full, send the data through UDP

    if (datacount == 9)
    {
       datacount = 0;
      for (int i=0;i<10;i++)
      {
      UDP.beginPacket(udpAddress , udpPort);
      UDP.print(uraw1[i]);
      UDP.endPacket();
      }   
    }
   else
    {
      datacount++;
    }
   
   // You can the amount of time to whatever you want
   // You can even change the delay to delayMicroseconds if you want to

   delay(10);

}
