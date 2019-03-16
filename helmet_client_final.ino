#include <WiFi.h>
#include <Wire.h>

#include <RTClib.h>


// your network name also called SSID
char ssid[] = "Aakriti";
// your network password
char password[] = "aakriti143";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

uint16_t port = 23;     // port number of the server//TCP, UDP with telnet protocol: encrypted text communication
IPAddress server(192,168,43,224);   // IP Address of the server
WiFiClient client;

#define alcPin 31
#define irPin 32
#define buzPin 10
int alc,vib,flag=0;
RTC_Millis RTC;

void setup()
{
  Serial.begin(9600);
  pinMode(alcPin,INPUT);
  pinMode(irPin,INPUT);
  pinMode(buzPin,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

 Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED)
  {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
 Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  
  // you're connected now, so print out the status  
  printWifiStatus();

  
  // attempt to connect to the server
  Serial.println("Attempting to connect to server");

uint8_t tries = 0;
  while (client.connect(server, port) == false)
  {
    Serial.print(".");
    if (tries++ > 100) {
      Serial.println("\nThe server isn't responding");
      while(1);
    }
    delay(100);
  }
  
  //we've connected to the server by this point
  Serial.println("\nConnected to the server!");


}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

}

void loop()
{
  alc=digitalRead(alcPin);
  int ir=digitalRead(irPin);
  
  if(ir==1 && alc==HIGH)
  {
    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(RED_LED,LOW);
    digitalWrite(buzPin,LOW);
    int buffer1=1;
   
    //send the serial command to the server
    client.println(buffer1);
  
    Serial.print("Sent: ");
    Serial.println(buffer1);
  }
  else
  {
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(RED_LED,HIGH);
    digitalWrite(buzPin,HIGH);
    int buffer1=0;
   
    //send the serial command to the server
    client.println(buffer1);
    Serial.print("Sent: ");
    Serial.println(buffer1);
  }
  delay(300);

  if (client.available())
  {
    char buffer[255] = {0};
    client.read((uint8_t*)buffer, client.available());
    Serial.print("Received: ");
    Serial.println(buffer);
}
}
