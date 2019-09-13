  /*
   * Sensors: soil_humidity: 16
   * Actuator: Pump: 5
   */
#include <ESP8266WiFi.h>;
 
#include <WiFiClient.h>;
 
#include <ThingSpeak.h>;

#include <Servo.h>

Servo myservo;
 
const char* ssid = "realme 3 Pro"; //Your Network SSID
 
const char* password = "141436733e9a"; //Your Network Password
 
int val;
 
 
WiFiClient client;
 
unsigned long myChannelNumber = 795684; //Your Channel Number (Without Brackets)
 
const char * myWriteAPIKey = "DSOYN4XCP4HHSYIF"; //Your Write API Key
const char * myReadAPIKey = "M4JPIFBL8GPLKIFG";
int statusCode=0;
 
void setup()
 
{
 
Serial.begin(9600);
 
delay(10);
pinMode(16,INPUT_PULLUP); //D0
myservo.attach(5); //D1

// Connect to WiFi network
 
WiFi.begin(ssid, password);
ThingSpeak.begin(client);
}
 
 
 
void loop()
 
{
  int pos;
 
  val = analogRead(0); //Read Analog values and Store in val variable

  Serial.println(val);
 
  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
 
  long count = ThingSpeak.readLongField(myChannelNumber, 2, myReadAPIKey);  
  
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Pump: " + String(count));
    if(count==1)
    {
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
    }

    if(val<500 && count!=1)
    {
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
    }
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  delay(15000); // No need to read the counter too often.
  
 
 
}
