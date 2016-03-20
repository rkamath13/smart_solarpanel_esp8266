#include <ArduinoJson.h>

#include <SparkFunTSL2561.h>
#include <Wire.h>
#include<ESP8266WiFi.h>
#define TEMP_REG 0x05
#define I2C_ADDR 0x18
#include <string.h>

SFE_TSL2561 light;

const char* ssid     = "enter your ssid";
const char* password = "enter the password";
int area = 4;
const char* host = "enter the host web server";
String Sensors;
unsigned int data0, data1;
float effp = 0.12;
float tcp = -0.0045;
boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds
float temp, irr; 
float power, eff;
String temp1,irr1, power1, eff1;
//char *power1;
//char *eff1;
int flag = 0;
int valve = 0;
int sys = 0;
int thresh = 0;
char* jsonchar;
//int syst[][] = {};
//String power2 , eff2;
 

String url;
void setup(void) {
  Serial.begin(9600);
  delay(1000);
  pinMode(BUILTIN_LED, OUTPUT);  
  digitalWrite(BUILTIN_LED,HIGH);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
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
  Wire.begin();  

  light.begin();
  gain = 0;

   // If time = 0, integration will be 13.7ms
  // If time = 1, integration will be 101ms
  // If time = 2, integration will be 402ms
  // If time = 3, use manual start / stop to perform your own integration
  unsigned char time = 1;
  light.setTiming(gain,time,ms);
  light.setPowerUp();

}

void loop(void) {
   WiFiClient client;

  if(sys == 0)
  {
    digitalWrite(BUILTIN_LED, HIGH); 
     digitalWrite(2, LOW);
     
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
    url = "/home/send_data/0/0/0/0";
  Serial.print("Requesting URL: ");
  Serial.println(url);
   // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  
  String line;
               
  delay(500); 
   while(client.available()){
  line = client.readStringUntil('\n');
  Serial.println(line);
    }

  //Serial.println(line.toCharArray(buf,100));
  
  //char * buf = (char*) malloc (sizeof(char) * line.length());  
  //sprintf (buf, "%s", line.c_str());
   char buf[line.length()+1];
  line.toCharArray(buf,line.length()+1);
  Serial.println("BUFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
  Serial.println(buf);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(buf);//(buf);
 // if () {
  //  Serial.println("parseObject() failed");
   // return; 
  //}
 sys = root["system"];


Serial.println("SYYYYYYYYYYYYYYYYYYyyyystem");
Serial.println(sys);
Serial.println("Threshhhhhhhhhhhhhhhh");
Serial.println(thresh);

  //free (buf);
    
} //sys if

else if(sys = 1)
{
 
   // This will send the request to the server

  if (light.getData(data0,data1))
  {
    // getData() returned true, communication was successful
    
    
    irr = data0*0.046;
    //dtostrf(irr, 4, 4, irr1);
    //Serial.print(" data1: ");
    //Serial.print(data1);
  }

  uint16_t t;
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(TEMP_REG);
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDR, 2);
  t = Wire.read();
  t<<=8;
  t=t | Wire.read();

  temp = t&0x0FFF;
  temp=temp/16;
 
  if(t&0x1000)
  temp = temp-256;
  //dtostrf(temp, 2, 0, temp1);
   //temp = 20;
  eff = effp+(tcp*effp*(temp-25));
  power = (effp*irr*area)-(area*irr*(effp-eff));
  
  //floatToString(eff1,eff,3);
  //floatToString(power1,power,3);
  
  //eff2 = eff1;
  //power2 = power1;
 
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Irradiance = ");
  Serial.println(irr);
  Serial.print("Efficiency = ");
  Serial.println(eff*100);
  Serial.print("Power = ");
  Serial.println(power);
  Serial.print("connecting to ");
  Serial.println(host);
  eff1 = String(eff*100);
  power1 = String(power);
  temp1 = String(temp);
  irr1 = String(irr);
  //Serial.println(eff1 + "  " +power1);
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  Sensors = temp1+"/"+ irr1 +"/"+ eff1 +"/"+ power1;
  url = "/home/send_data/";
  url = url+Sensors;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  String line;
   // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500); 
   while(client.available()){
  line = client.readStringUntil('\n');
  Serial.println(line);
    }

  //Serial.println(line.toCharArray(buf,100));
  
  //char * buf = (char*) malloc (sizeof(char) * line.length());  
  //sprintf (buf, "%s", line.c_str());
  char buf[line.length()+1];
  line.toCharArray(buf,line.length()+1);
  Serial.println("BUFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
  Serial.println(buf);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(buf);//(buf);
 // if () {
  //  Serial.println("parseObject() failed");
   // return; 
  //}
 sys = root["system"];
thresh = root["threshold"];
valve = root["valve"];

Serial.println("SYYYYYYYYYYYYYYYYYYyyyystem");
Serial.println(sys);
Serial.println("Threshhhhhhhhhhhhhhhh");
Serial.println(thresh);
Serial.println("VAAAAAAAAAALVE");
Serial.println(valve);

  //free (buf);
  
  if((valve == 1)||(temp>=thresh))
   {
   
      digitalWrite(BUILTIN_LED, LOW); 
     digitalWrite(2, HIGH);
   }
   else if((valve == 0)||(temp<thresh))
    {
       digitalWrite(BUILTIN_LED, HIGH); 
     digitalWrite(2, LOW);
      }
  
} //sys = 1
  delay(4000); 
}

