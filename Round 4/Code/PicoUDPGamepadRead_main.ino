// MREN 303 Pico W Wifi Gamepad Read
// Written For MREN 303 

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2; 
Servo myservo3; 

#ifndef STASSID
#define STASSID "MREN303_wifi"
#define STAPSK "MREN@303p1"
#endif

#define STBY 18
#define PWMA 21
#define AI1 19
#define AI2 20
#define PWMB 13
#define BI1 12
#define BI2 11
#define ENCA1 17
#define ENCB1 16 
#define ENCA2 14
#define ENCB2 15

unsigned int localPort = 8888;  // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];  // buffer to hold incoming packet,
char ReplyBuffer[22] = "acknowledged\r\n";        // a string to send back
// char Arrays to match commands from gamepad 
char stringA[17] =    "A Button Press";
char stringB[17] =    "B Button Press";
char stringY[17] =    "Y Button Press";
char stringX[17] =    "X Button Press";
char stringLB[17] =   "LB Button Press";
char stringRB[17] =   "RB Button Press";
char stringLS[17] =   "L Stick Press";
char stringRS[17] =   "R Stick Press";
char stringBack[17]=  "Back Press";
char stringStart[17]= "Start Press";
char stringUp[17] =   "Up Dpad Press";
char stringDown[17] = "Down Dpad Press";
char stringLeft[17] = "Left Dpad Press";
char stringRight[17]= "Right Dpad Press";
char stringLX[17] =   "L Stick X Value ";
char stringLY[17] =   "L Stick Y Value ";
char stringRX[17] =   "R Stick X Value ";
char stringRY[17] =   "R Stick Y Value ";
char stringLT[17] =   "L Trigger Value ";
char stringRT[17] =   "R Trigger Value ";

int valueLx = 0;
int valueLy = 0;
int valueRx = 0;
int valueRy = 0;
int valueLt = 0;
int valueRt = 0; 
int batteryLevel = 0;

int ledState = 0;
bool pollBattery = false; 

int posA = 0;
int posB = 0;

//game modes
const int IDLE_MODE = 0;
const int AUTO_MODE = 1;
const int MANUAL_MODE = 2;
int current_mode = IDLE_MODE; // Variable to store the current mode. Starts in idle mode

unsigned long startTime = 0;  // Variable to store the start time
unsigned long currentTime = 0; // Variable to store the current time

WiFiUDP Udp;

void setup() { //This handles network function and runs on core 1
  Serial.begin(115200);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);

}
void setup1(){ //This handles all inputs and outputs and runs on core 2
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,0);
  myservo1.attach(2, 544, 2500);
  myservo2.attach(3, 544, 2500);
  myservo3.attach(4, 544, 2500);
  analogReadResolution(12); // 12 bit resolution = 0 - 4096 (2^12)
  // Initialize motor driver pins as outputs
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoderA1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA2), readEncoderA2, RISING);

  pinMode(PWMA, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);

}

void loop() { //This loop executes on Core 1 of the Pico, handles networking and recieves commands
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d)\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort(), Udp.destinationIP().toString().c_str(), Udp.localPort());

    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;

    char comparisonString[17] = "";
    char valueString[5] = "";

    for (int i=0; i<16 ; i++){
      comparisonString[i]=packetBuffer[i];
    }
    comparisonString[16] = 0;
    
    Serial.println("Comp String:");
    Serial.println(comparisonString);

    if (strcmp(comparisonString,stringA) == 0){
      if (current_mode == IDLE_MODE){ // You can only go to auto mode from idle mode
        Serial.println("Setting mode to auto");//this line may be removed for final version
        current_mode = AUTO_MODE; // Change to auto mode
        startTime = millis();  // Start recording the time
 
      }           
    }
    if (strcmp(comparisonString,stringB) == 0){
      Serial.println("Setting mode to manual");//this line may be removed for final version
      current_mode = MANUAL_MODE; // Change to manual mode

    }
    if (strcmp(comparisonString,stringY) == 0){
      Serial.println("Setting mode to idle");//this line may be removed for final version
      current_mode = IDLE_MODE; // Change to idle mode
    }   
    if (strcmp(comparisonString,stringStart) == 0){
      Serial.println("Polling Battery Level");
      pollBattery = true;
      char pollBatteryMessage[] = "Polling Battery Level"; 
      memcpy(ReplyBuffer,pollBatteryMessage,22);
    }
    if (strcmp(comparisonString,stringLX) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueLx = atoi(valueString);
      Serial.println("LX Value is:");
      Serial.println(valueLx);
    }
    if (strcmp(comparisonString,stringLY) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueLy = atoi(valueString);
      Serial.println("LY Value is:");
      Serial.println(valueLy);
    }
    if (strcmp(comparisonString,stringRX) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueRx = atoi(valueString);
      Serial.println("RX Value is:");
      Serial.println(valueRx);
    }
    if (strcmp(comparisonString,stringRY) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueRy = atoi(valueString);
      Serial.println("RY Value is:");
      Serial.println(valueRy);
    }
    if (strcmp(comparisonString,stringRT) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueRt = atoi(valueString);
      Serial.println("RT Value is:");
      Serial.println(valueRt);
    }
    if (strcmp(comparisonString,stringLT) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueLt = atoi(valueString);
      Serial.println("LT Value is:");
      Serial.println(valueLt);
    }
    

    // send a reply, to the IP address and port that sent us the packet we received
    if(pollBattery){ //Wait for battery read to reply 
      delay(20);
    }
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}

void loop1(){ //This Runs on Core 2 and performs all inputs and outputs
  if(pollBattery){
    readBattery();
    pollBattery = false;
  }
  currentTime = millis();

  // After spending more than 30 s in auto mode:
  if ((current_mode == AUTO_MODE) && (currentTime - startTime) >= 30000) {
    Serial.println("TIME OUT: changing to manual mode");//this line may be removed for final version
    current_mode = MANUAL_MODE; // Change to manual mode
  }
  studentCode(current_mode);
  
}

// YOUR CODING GOES HERE
void studentCode(int current_mode){ 
  if(current_mode == IDLE_MODE){
    digitalWrite(LED_BUILTIN,0);

   Serial.println("You are in idle mode");//this line may be removed for final version
   digitalWrite(LED_BUILTIN, LOW); // LED is off for idle mode
    // No further action required
  }
  else if (current_mode == AUTO_MODE){
    Serial.println("You are in auto mode");//this line may be removed for final version
    digitalWrite(LED_BUILTIN, LOW); // LED is off for auto mode
    // Write additional commands for autonomous mode
    //CAUTION: YOU CANNOT PRESS ANY BUTTONS WHILE IN AUTO MODE UNLESS YOU PASS THE GATE (in this case, press B to go to manual mode)
  }
  else if (current_mode == MANUAL_MODE){
    digitalWrite(LED_BUILTIN,1);
    digitalWrite(LED_BUILTIN, HIGH); // LED is on for manual mode
    // Write additional commands for manual mode
    int servoPos = map(valueLt,0,255,0,180);
    myservo1.write(servoPos);
    myservo2.write(servoPos);
    myservo3.write(servoPos);


    //Forward and Backwards
    int dir = 1;
    if(valueRy < 0) 
      dir = -dir; 
         
    //Right and Left Turning
    int turnDir = 1;
    if(valueLx < 0) 
      turnDir = -turnDir; 
    
    if (abs(valueRy) < 130 && abs(valueRy) >= 30)
      valueRy = 130;
    else if (abs(valueRy) < 30)
      valueRy = 0;
 
    if (abs(valueLx) < 130 && abs(valueLx) >= 30)
      valueLx = 130;
    else if(abs(valueLx) < 30)
      valueLx = 0;

    if (abs(valueLx) < 30){
      setMotor(-dir, abs(valueRy), PWMA, AI1, AI2);
      setMotor(dir, abs(valueRy), PWMB, BI1, BI2);
    }
    else if (abs(valueRy) < 30){  
      setMotor(turnDir, abs(valueLx), PWMA, AI1, AI2);
      setMotor(turnDir, abs(valueLx), PWMB, BI1, BI2);
    }
    else{
      setMotor(0, abs(valueLx), PWMA, AI1, AI2);
      setMotor(0, abs(valueLx), PWMB, BI1, BI2);
    }
  }
  return;
}

void setMotor(int dir, int pwmVal, int pwm, int i1, int i2){
  analogWrite(pwm, pwmVal);
  if(dir == 1){
    digitalWrite(i1, HIGH);
    digitalWrite(i2, LOW);
  }
  else if(dir == -1){
    digitalWrite(i1, LOW);
    digitalWrite(i2, HIGH);
  }
  else{
    digitalWrite(i1, LOW);
    digitalWrite(i2, LOW);
  }
}

void readEncoderA1() {
  int b1 = digitalRead(ENCB1);
  if (b1 > 0) {
    posA++;
  } else {
    posA--;
  }
}

void readEncoderA2() {
  int b2 = digitalRead(ENCB2);
  if (b2 > 0) {
    posB++;
  } else {
    posB--;
  }
}
void readBattery(){
  // battery voltage = 1.0V - 1.4V / cell * 4 cells = 4.0V - 5.6V 
  // Too high a voltage for Pico IO, 
  // Use voltage ladder (2 high value resistors connected in series between power and ground, attach an analog read to middle) to convert to 2.0V - 2.8V
  // Pico IO max 3.3V so to map maximum and minimum battery level:   
  // (4096 max value read/ 3.3V max voltage) * 2.0V = 2482 min value,(4096 max value read/ 3.3V max voltage) * 2.8V = 3475 max value    
  // Therefore 2482-3475 is our range for battery level 
  int voltage = analogRead(27);
  //Serial.println("Voltage reading is:");
  //Serial.println(voltage);
  //if (voltage < 200) {
    //Serial.println("Battery Not Connected");
  //}
  //else{
    batteryLevel = map(voltage,2482,3475,0,100);
    char batteryMessage[] = "Battery Level is: %d %";
    sprintf(ReplyBuffer,batteryMessage,batteryLevel);
    //Serial.println("Battery Level is :");
    //Serial.print(batteryLevel); 
    //Serial.print("% \n");  
  }
