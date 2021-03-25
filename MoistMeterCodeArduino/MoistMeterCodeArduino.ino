  
  
  #include <Wire.h>
  #include "rgb_lcd.h"
  #include <Bridge.h>
  #include <HttpClient.h>
  
  #define SensorPin A0 

  rgb_lcd lcd;
   
  //PushingBox Scenario DeviceID:
  char devid[] = "v4E4869B91BEC8D7";
  
  char serverName[] = "api.pushingbox.com";
  boolean DEBUG = true;
  int id = 1; // Each sensor would have a seperate ID

  const int colorR = 0;
  const int colorG = 0;
  const int colorB = 255;

  void setup() 
  {
    Bridge.begin();    
    Serial.begin(9600);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    //Set the LCDs color
    lcd.setRGB(colorR, colorG, colorB);
    //Print a messege to the LCD
    lcd.print("Current MOIST:");
    // wait for a serial connection
    while (!Serial); 
  }

  void loop() 
  {
    
    //Initialise the client library
    HttpClient client;

    //Setup sensorValue to read a value from Analog Port A0
    float sensorValue = analogRead(A0);
 
    //Make a HTPP request:
    String APIRequest;
    APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=" + id +"&TimeStamp=50&TempC="+sensorValue;
    client.get (APIRequest);

    // if there are incoming bytes available from the server, read them and print them:
    while (client.available()) 
    {
      char c = client.read();
    }

    //average of 100 sensor data to make the data more stable and accurate.
    for (int i = 0; i <= 100; i++) 
    { 
      sensorValue = sensorValue + analogRead(SensorPin); 
      delay(1); 
    } 

    //Divides the 100 sensor data by 1000 to get moisture %
    sensorValue = sensorValue/1000.0;

    //Subtract the 'sensorValue' from a 100 to get the % of moisture in the dirt
    int valueToSend = 100 - sensorValue;

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0,1);
    lcd.print(valueToSend);
      
    Serial.println(valueToSend);
    delay(1000);//Post every second
    //delay(60000);//Posr results every minute 
    //delay(1800000); //Post results every 30 minutes
    Serial.flush();
  } 
