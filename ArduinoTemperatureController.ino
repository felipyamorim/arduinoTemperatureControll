#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
#define DS18B20 D2          //DS18B20 is connected to GPIO Pin 2

String apiKey = "xxx";     //  Enter your Write API key from ThingSpeak
const char* ssid =  "xxx";     // Enter your WiFi Network's SSID
const char* pass =  "xxx"; // Enter your WiFi Network's Password
float temp;
float setPoint = 25.5;
float tempAction = 0.7;
bool relayActivated = false;

 
OneWire ourWire(DS18B20);
DallasTemperature sensor(&ourWire);
WiFiClient client;

int porta_rele = D1;
 
void setup() 
{
       pinMode(porta_rele, OUTPUT); 
       digitalWrite(porta_rele, LOW);
       Serial.begin(115200);
       delay(1000);
       sensor.begin();
 
       Serial.print("Connecting to: ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(100);
            Serial.print("*");
     }
      Serial.println("");
      Serial.println("***WiFi connected***");
 
}
 
void loop() 
{
  
      sensor.requestTemperatures();
      temp = sensor.getTempCByIndex(0);
    
      Serial.println("Temperatura: " + String(temp));

      if(temp != -127.00){
         if(relayActivated){
            if(temp >= setPoint){
                 relayActivated = false;
                 digitalWrite(porta_rele, LOW);
            }
         }else{
           if(temp <= (setPoint - tempAction)){
                relayActivated = true;
                digitalWrite(porta_rele, HIGH);
           }        
         }
      }else{
        Serial.println("Erro na sonda, verifique se a mesma esta encaixada corretamente!");
        digitalWrite(porta_rele, LOW);
      }

        HTTPClient http;  //Declare an object of class HTTPClient
       
          http.begin("http://www.xxx.com/monitor.php?api_key="+apiKey+"&temperatura="+String(temp));  
          int httpCode = http.GET();                                                                  
          Serial.println("Sending...");
          /*if (httpCode > 0) { //Check the returning code
            Serial.print("Return status: " + httpCode);
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                    //Print the response payload
       
          }*/       
          http.end();   

      delay(3000);
}
