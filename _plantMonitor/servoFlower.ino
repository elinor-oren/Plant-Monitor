#include <Servo.h> //includes the correct library
Servo myservo; //creates a servo object 
int angle = 0; //sets initial servo position
moisture = "0"

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Moisture condition [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Check the incoming MQTT message
  if ((char)payload[0] == '1') {
    // If the message starts with '1', move the servo to a specific position (e.g., 90 degrees)
    servo.write(90);
    delay(1000);
    servo.write(0);
  } else if ((char)payload[0] == '0') {
    // If the message starts with '0', move the servo to another position (e.g., 0 degrees)
    servo.write(0);
  } else {
    // Handle other cases or unrecognized messages
    Serial.println("Unrecognized message");
  }
}

void setup() {
  servo.attach(13); //sets servo to pin 13
  servo.write(angle);
  Serial.begin(115200); //publish to the Serial for debugging 

}

void loop() 
{ 
  Serial.println(angle);
    moisture = Serial.read();
    Serial.println(moisture);
    // 1 = activates flag upward, 0 = activates flag downward
    if (moisture == '1' && angle == 10){
      for(angle = 10; angle < 180; angle++)  
      {                                  
        servo.write(angle);               
        delay(15);                   
      } 
    // now scan back from 180 to 0 degrees
    for(angle = 180; angle > 10; angle--)    
    {                                
      servo.write(angle);           
      delay(15);       
    } 
  }



  
