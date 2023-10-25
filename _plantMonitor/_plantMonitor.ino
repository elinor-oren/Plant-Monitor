/*
 *  Simple HTTP get webclient test
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//Wifi and MQTT
#include "arduinosecrets.h"
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

const char* mqtt_server = "enter mqtt url";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

pinMode(BUILTIN_LED, OUTPUT);     
digitalWrite(BUILTIN_LED, HIGH);  

client.setServer(mqtt_server, 1884);
client.setCallback(callback);

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
 
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/testwifi/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  sendMQTT();
}

void sendMQTT(){
  //sends a message to both the Serial + client monitor so that we can see what has been sent 
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  ++value; 
  snprintf(msg, 50,"hello world #%ld", value);
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucbvren", msg) 
}

void reconnect (){
//Loop until we're reconnected 
while (!client.connected()) {
  Serial.print("Attempting MQTT connection...");
  String clientID = "ESP8266Client-";
  //Creates a random client ID (+= adds and sets new value to the sum) 
  clientId += String(random(0xffff), HEX);
//the 0X indicates that it is a hex number and that is the only purpose of 0X. 
//To convert the hex number 0XFFFF to decimal (or any other hexadecimal number for that matter), you follow these steps:
//Multiply the last digit by 1, Multiply the second to last digit by 16, Multiply the third to the last digit by 16 x 16, Multiply the fourth to the last digit by 16 x 16 x 16, Multiply the fifth to the last digit by 16 x 16 x 16 x 16 and so on until all the digits are used.
  //Attempt to connect 
  if(client.connect(clientID.c_str(), mqttuser, mqttpass)){
    Serial.println("connected");
    client.subscribe("student/CASA0014/plant/ucbvren/inTopic");

  }
  else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println("try again in 5 seconds");
    delay(5000);
    //waits 5 seconds
  }
}
}
void callback(char* topic, byte* payload, unassigned int length){
  //The callback function processes messages that have been subscribed to by the sketch. 
  Serial.print("message arrived[");
  Serial.print(topic);
  Serial.print("]");
  for (int i=0; i<length; i++){
    Serial.print((char)payload[i]);
    //bro idk what this line means
  }
  Serial.println();

  //Switch on LED if 1 received 
  if((char)payload[0]=='1'){
    digitalWrite(BUILTIN_LED, LOW); //turns the LED on, which is counterintuitive?? 
   } else{
      digitalWrite(BUILTIN_LED, HIGH);// TUrn the LED off by turning the voltage high
    }
    }
  }
  }
}
