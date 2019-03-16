#include <WiFi.h>
#include <RTClib.h>
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "6TD3SKH61R1RCL0N";
char buffer[255];
RTC_Millis RTC;
WiFiClient clients;  //for thingspeak
WiFiClient client; 
WiFiClient client2;
float conval1;
boolean alreadyConnected = false;
boolean alreadyConnected2 = false;
char ssid[] = "Anda";
char password[] = "hello123";
int motion1=0;
int motion2=0;
WiFiServer port(23);
//WiFiServer port2(25);

boolean lastConnected = false;                 // state of the connection last time through the main loop
int failedCounter = 0;


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  RTC.begin(DateTime(__DATE__, __TIME__));
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");  
  while (WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nIP Address obtained");
  printWifiStatus();
  port.begin();
  //port2.begin();
  pinMode(31,OUTPUT);
}
void loop() {
  DateTime now = RTC.now();
    
    client = port.available();
    if (client) {
      if(!alreadyConnected) {
      // clear out the input buffer:
      client.flush();
      Serial.println("We have a new client from port1");
      client.println("Hello, client1!");
      
      alreadyConnected = true;
    }
    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char buffer1[1];
      client.read((uint8_t*)buffer1, client.available());
       Serial.println("Recieved");
       Serial.println(buffer1);
       if(buffer1[0]=='1')
       {
        digitalWrite(31,HIGH);
       }
       else if(buffer1[0]=='0')
       {
        digitalWrite(31,LOW);
       }
      // updateThingSpeak("field2="+String(buffer1));
      
           
          }
    }


   /*client2 = port2.available(); 
    if (client2) {
      if (!alreadyConnected2) {
      // clear out the input buffer:
      client2.flush();
      Serial.println("We have a new client from port2");
      client2.println("Hello, client!");
      alreadyConnected2 = true;
      }  
      if (client2.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client2.read();
      char buffer[255] = {0};
      client2.read((uint8_t*)buffer, client2.available());
      float conval = atof(buffer);
      motion2 += conval;
      Serial.print("Port 2 client data: ");
      Serial.println(motion2);   
      }
     
      }*/
    
}


/*void updateThingSpeak(String tsData)
{
   Serial.println("Date string: " + tsData);
    
    Serial.println("...Connecting to Thingspeak");
    
    // Connecting and sending data to Thingspeak
    if(clients.connect("api.thingspeak.com", 80))
    {
        Serial.println("...Connection succesful, updating datastreams");
        
        clients.print("POST /update HTTP/1.1\n");
        clients.print("Host: api.thingspeak.com\n");
        clients.print("Connection: close\n");
        clients.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
        clients.print("Content-Type: application/x-www-form-urlencoded\n");
        clients.print("Content-Length: ");
        clients.print(tsData.length());
        clients.print("\n\n");
        
        clients.println(tsData); //the ""ln" is important here.
    
        // This delay is pivitol without it the TCP client will often close before the data is fully sent
        delay(200);
        
        Serial.println("Thingspeak update sent.");
    }
    else{
        // Failed to connect to Thingspeak
        Serial.println("Unable to connect to Thingspeak.");
    }
    
    if(!clients.connected()){
        clients.stop();
    }
    clients.flush();
    clients.stop();
}

*/
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
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

