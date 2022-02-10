




//********************************************************************************
// Hai Welcome To WaterManagement Project :-)                
// In this Project ,I used firebase and kodular app for notification and control .
// I Hope You like the project for any doubt contact : aswath.raviji@gmail.com
//$$$$$ Let Your Code Conquer The World $$$$$
//*********************************************************************************


#include <ESP8266WiFi.h> 
#include <FirebaseESP8266.h>  
 
const char* ssid = "***Enter your SSID*****";  
 
// The SSID (name) of the Wi-Fi network you want to connect to  
 
 
const char* password = "****Enter your SSID Password***"; 
FirebaseData firebaseData; 
 
#define FIREBASE_HOST "****Enter your Firebase Hostname*****"  
 
#define FIREBASE_AUTH "****Enter your Firebase Auth Token****"  
 
 
int ledr = 14;    // LedRed    D5 Pin 
int ledo = 12;   // LedOrange D6 Pin
int ledg = 13;  //  LedGreen  D7  Pin
int buzz = 2;  //   Buzzer    D4  Pin
 
#define w1 4   // WaterLevelSensor1 D2 Pin
#define w2 5  //  WaterLevelSensor2 D1  Pin
 
int relay = 0;//  Relay ToControl ACMotor D3 Pin
void setup()  
{ 

digitalWrite(LED_BUILTIN,LOW);  
Serial.begin(115200);  
 
// Start the Serial communication to send messages to the computer  
 
delay(10);  
Serial.println('\n');  
WiFi.begin(ssid, password);  
 
// Connect to the network  
 
Serial.print("Connecting to ");  
Serial.print(ssid);  Serial.println(" ...");  int i = 0;  
 
while (WiFi.status() != WL_CONNECTED)  
 
{ 
 
 // Wait for the Wi-Fi to connect  
 
delay(1000);  
Serial.print(++i);  
Serial.print(' ');  
}  
 
Serial.println('\n); 
 
Serial.println("Connection established!");
digitalWrite(LED_BUILTIN,HIGH);  
Serial.print("IP address:\t");  
Serial.println(WiFi.localIP());  
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
Firebase.reconnectWiFi(true);   

//PinMode Configuration
 
pinMode(w1,INPUT_PULLUP); 
pinMode(w2,INPUT_PULLUP); 
pinMode(LED_BUILTIN,OUTPUT);  
pinMode(relay,OUTPUT);               
pinMode(ledr,OUTPUT);  
pinMode(ledo,OUTPUT);  
pinMode(ledg,OUTPUT); 
pinMode(buzz,OUTPUT);  

//Initializing all pins as Low


digitalWrite(ledr,LOW);
digitalWrite(ledo,LOW);  
digitalWrite(ledg,LOW); 
digitalWrite(buzz,LOW);  
digitalWrite(relay,LOW);  
 
// put your setup code here, to run once: 
  
} 
 
 void loop() 
 
 {  
 // put your main code here, to run repeatedly:  
 
if (digitalRead(w1)==HIGH)  
 
{ 
 
Firebase.setString(firebaseData,"water/w2","water_half");  
 
digitalWrite(buzz,LOW);  
digitalWrite(ledr,LOW);  
digitalWrite(ledo,HIGH);
  
if (digitalRead(w2)==HIGH)  
 
{ 
 
Firebase.setString(firebaseData,"water/w1","water_overflowing");
 digitalWrite(ledg,HIGH); 
 
delay(500);  
digitalWrite(buzz,HIGH); 
delay(2000); 
digitalWrite(buzz,LOW);  
 
} 
  
else 
  
{ 
 
Firebase.setString(firebaseData,"water/w1","water_not_over");  
 
digitalWrite(ledg,LOW); 
digitalWrite(buzz,LOW);  
 
} 
 
 } 
 
else 
  { 

Firebase.setString(firebaseData,"water/w2","water_dry");  
 
digitalWrite(ledo,LOW);  
digitalWrite(ledg,LOW);  
digitalWrite(ledr,HIGH); 
digitalWrite(relay,HIGH);  
digitalWrite(buzz,HIGH);  
delay(1000);  
digitalWrite(buzz,LOW);  
 
}   
} 
