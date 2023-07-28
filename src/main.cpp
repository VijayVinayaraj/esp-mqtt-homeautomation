#include <Arduino.h>
#include "EspMQTTClient.h"

#define WIFINAME "hloo"
#define WIFIPASSWORD "qwpoaslk"
#define IP "192.168.159.56"
#define PORT 1883
#define CLIENTNAME "automation"

#define led 33

EspMQTTClient client(
  WIFINAME,
  WIFIPASSWORD,
  IP,  // MQTT Broker server ip
  CLIENTNAME,     // Client name that uniquely identify your device
  PORT              // The MQTT port, default to 1883. this line can be omitted
);

void toggleLed(bool toggle){
  if (toggle == true){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
}




void mqttSendMessage(String message){

if(client.isMqttConnected()){

// client.publish("home",message);
//     delay(800);

client.subscribe("home", [](const String & payload) {
    if(payload.toInt() == 1){
      Serial.println("dfd");
      toggleLed(true);
    }else if (payload.toInt() == 0){
      toggleLed(false);
    }
  });
}

}

void mqttInit(){
   client.enableDebuggingMessages();
   void enableMQTTPersistence();
}


void onConnectionEstablished()
{
  mqttSendMessage("hi");
}








void mqttLoop(){

    client.loop();
}


void setup(){
  Serial.begin(115200);
  mqttInit();
  pinMode(led,OUTPUT);
}


void loop(){
  
  mqttLoop();
}