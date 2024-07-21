#define BLYNK_TEMPLATE_ID "TMPL5P82vBgpF"
#define BLYNK_TEMPLATE_NAME "IRRIGATION DATA MONITORING AND CONTROL PANEL"
#define BLYNK_AUTH_TOKEN "du10apPN_rtC11q5zuZmD8zU7JTDOyd-"
//Include the library files
//#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define sensor 34
#define relay 4
int value;




BlynkTimer timer;

// Enter your Auth token
char auth[] = "du10apPN_rtC11q5zuZmD8zU7JTDOyd-";

//Enter your WIFI SSID and password
char ssid[] = "Elly";
char pass[] = "elly9977";

void setup() {
  // Debug console
  Serial.begin(921600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

}

//Get the  moisture sensor values and map them to 100
void soilMoisture() {
  value = analogRead(sensor);
  value = map(value, 0,4095, 0, 100);
  value = (value - 100) * -1;
  Blynk.virtualWrite(V0, value);
  Serial.println(value);
  
}
//Enabling the  pump to  automatically  be controlled
void automaticControl(){
  if(value<=20){
    digitalWrite(relay,HIGH);
  }
  if(value>=56){
    digitalWrite(relay,LOW);
  }
}

//Get the button value
BLYNK_WRITE(V1) {
  /*bool Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(relay, LOW);
   
  } else {
    digitalWrite(relay, HIGH);
    
  }*/
   digitalWrite(relay,LOW);
  if(param.asInt()==1){
    digitalWrite(relay,HIGH);
  }
  else{
    digitalWrite(relay,LOW);
  }
}

void loop() {
  automaticControl();
  soilMoisture();
  Blynk.run();//Run the Blynk library
  delay(200);
  

}