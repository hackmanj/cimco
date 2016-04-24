// written by Joe Hackman - www.managedsolutions.com GPL v3 License
#include <dht.h>
#include <SPI.h>
#include <Ethernet.h>

String stringOne, stringTwo, stringThree, stringFour;

//Assigning IP Address, Mac and Server IP for DNC Max
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 89, 233 };
byte server[] = { 192, 168, 89, 241 }; //This is the IP address of your DNC Max Server

EthernetClient client;

//DHT11 Goodies, Need to access A0 on the Uno to get Temp/Humid
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
void setup() {

Ethernet.begin(mac, ip);
  Serial.begin(9600);

  delay(1000);
Serial.println("connecting...");

  if (client.connect(server, 4442)) {
    Serial.println("connected");
    //Replace or remove next line
    //client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");

//DHT11 Reporting in
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
 
  delay(1000);//Wait before accessing Sensor
}
}
void loop() {
  
DHT.read11(dht_apin);

stringOne = (DHT.temperature*5);
stringTwo = ("FILE:COOLANTTEMP|");
stringThree = ("\n");
stringFour = stringTwo + stringOne + stringThree;

client.connect(server, 4442);
Serial.println(stringFour);
client.print("MONITORMESSAGE\n");
client.print("PORTID:AMC4\n");
client.print("FILECOUNT:1\n");
client.print(stringFour);
client.stop();
delay(60000);
}
