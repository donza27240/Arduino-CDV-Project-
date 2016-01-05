#include "SPI.h"
#include "Ethernet.h"

const int ry1 = 7;
const int ry2 = 5;
const int ry3 = 3;
const int ry4 = 1;


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
/*byte ip[] = { 192, 168, 1, 2 }; // ip in lan
/*byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask*/
EthernetServer server(80); //server port

String readString; 

//////////////////////

void setup(){

  pinMode(ry1, OUTPUT); //pin selected to control
  pinMode(ry2, OUTPUT);
  pinMode(ry3, OUTPUT);
  pinMode(ry4, OUTPUT);

    
  //start Ethernet
  Ethernet.begin(mac);
  Serial.println("server LED test"); // Test 
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        
        if (readString.length() < 100) {

          
          readString += c; 
          
        } 

        
        if (c == '\n') {

          ///////////////
          Serial.println(readString); //print to serial monitor for debuging 

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          

          client.println("<h1>Light Controller</h1><br>");
          
          
          // DIY buttons
          client.println("Room 1");
          
          client.println("<a href= /on1><h1>ON</h1></a>"); 
          client.println("<a href = /off1><h1>OFF</h1></a>"); 
          
          client.println("Room 2");

          client.println("<a href= /on2><h1>ON</h1></a>"); 
          client.println("<a href = /off2><h1>OFF</h1></a>"); 

          client.println("Room 3");

          client.println("<a href= /on3><h1>ON</h1></a>"); 
          client.println("<a href = /off3><h1>OFF</h1></a>");

          client.println("Room 4");

          client.println("<a href= /on4><h1>ON</h1></a>"); 
          client.println("<a href = /off4><h1>OFF</h1></a>");
          
         
          client.println("");
          client.println("");
 
          delay(1);
          
          client.stop();

          ////LOW=on////HIGH=off
          ///////////////////// control arduino pin
          if(readString.indexOf("on1") >0)//checks for on
          {
            digitalWrite(ry1, LOW);    // set pin 7 on
            Serial.println("Led On");
          }
          if(readString.indexOf("off1") >0)//checks for off
          {
            digitalWrite(ry1, HIGH);    // set pin 7 off
            Serial.println("Led Off");
          }
          
          if(readString.indexOf("on2") >0)//checks for on
          {
            digitalWrite(ry2, LOW);    // set pin 5 on
            Serial.println("Led On");
          }
          if(readString.indexOf("off2") >0)//checks for off
          {
            digitalWrite(ry2, HIGH);    // set pin 5 off
            Serial.println("Led Off");
          }

          if(readString.indexOf("on3") >0)//checks for on
          {
            digitalWrite(ry3, LOW);    // set pin 3 on
            Serial.println("Led On");
          }
          if(readString.indexOf("off3") >0)//checks for off
          {
            digitalWrite(ry3, HIGH);    // set pin 3 off
            Serial.println("Led Off");
          }

          if(readString.indexOf("on4") >0)//checks for on
          {
            digitalWrite(ry4, LOW);    // set pin 1 on
            Serial.println("Led On");
          }
          if(readString.indexOf("off4") >0)//checks for off
          {
            digitalWrite(ry4, HIGH);    // set pin 1 off
            Serial.println("Led Off");
          }
          readString="";

        }
      }
    }
  }
}
