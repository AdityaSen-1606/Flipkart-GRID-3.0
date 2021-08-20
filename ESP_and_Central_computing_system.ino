// Pins 2,3,4,5 (GPIO's) which we are use for driving our motor.
// Pins 13,14,15,16 (GPIO's) are used for stepper motor for actuator
// firstly we had to make the ip address of all esp8266 (node-mcu) static so that we can differentiate.


//IP address of the esp8266 1, 2, 3 & 4 are known then we can make them also static

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <Stepper.h>

// IP1 mean bot1 ...
int IP1;            // need to specify
Stepper tray(72, 12, 13, 14, 15); // 12 & 13 are used for clock wise rotation. 14 & 15 are used for anti-clockwise rotation


void setup() {
  pinMode(2,Output);          //inputs for motor 1
  pinMode(3,Output);
  pinMode(4,Output);          //inputs for motor 2
  pinMode(5,Output);

   void Stop();

  Serial.begin(115200);
  WiFi.begin(ssid,password);    //ssid and its password is known of the WIFi router through which the esp8266 is need to connect
  Serial.print ("Connection is set-up")
  Serial.print (WiFi.localIP());   //Print IP address over serial monitor........Basically we initially known the IP address

  while(WiFi.status() !=WL_CONNECTED){
    delay(1000);
    Serial.print("Connection is not set-up");
    Serial.println("......");
    }

//On the start of the relay python code need to send the url/start on the IP1 
//In the front of brown wall the python code need to send url /tray on the IP1
//on coming back to the starting line python code need to send url /stop to IP1 and simultaniously send url /start on the IP2

// Similarly this code is for the bot 2,3 & 4


  server.on("/start", Start);               // Call the 'Start' function when a client requests URI "/start"
  server.on("/tray", Tray);
  server.on("/stop", Stop);
  server.onNotFound(Error);                 // When a client requests an unknown URI (i.e. something other than "/"), call function "Error"
  server.begin();
  Serial.println("Sever Started");
}


void loop() {
 
     server.handleClient();
}

void Start() {                            //On receiving the url:/start the start function will execute
  digitalWrite (2,HIGH);
  digitalWrite (3,LOW);                  
  digitalWrite (4,HIGH);
  digitalWrite (5,LOW);
}

void Tray(){
  void Stop();
  tray.setSpeed(60);
  tray.step(72);
  int i=0;
  do{
    for(i;i=12;i++){
      tray.step(i);}
      }
      while (i<=12);   //tray will raise untill it make 60 degree rotation 
      delay(10000);
for (int i=12;i=0;i--){
 tray.step(i);}       // after droping the box tray will come down
      delay(500);

      void Backward();
    }

void Error(){
  server.send(404, "text/plain", "404: Error"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void Backward(){
  digitalWrite(2,LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5, HIGH);
  }

void Stop(){                      
  digitalWrite (2,LOW);
  digitalWrite (3,LOW);
  digitalWrite (4,LOW);
  digitalWrite (5,LOW);
  }
