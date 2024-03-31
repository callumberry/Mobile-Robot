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

int lsensor = 26; // Left Sensor on Analog Pin 2
int msensor = 28;
int rsensor = 27; // Right Sensor on Analog Pin 1

int leftVal;
int rightVal;

int whiteLevel = 700;
int blackLevel = 800;
int armDeg = 0;
int clawDeg = 20;  

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
char stringUp[17] =   "Up DPad Press";
char stringDown[17] = "Down DPad Press";
char stringLeft[17] = "Left DPad Press";
char stringRight[17]= "Right DPad Press";
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
int valueDpadUp = 0;
int valueDpadDown = 0;

bool DpadUp = false; 
bool DpadDown = false;
bool DpadLeft = false; 
bool DpadRight = false;  

int ledState = 0;

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
  myservo1.attach(6, 544, 2500);
  myservo2.attach(7, 544, 2500);

  myservo1.write(20); 
  myservo2.write(0);
  analogReadResolution(12); // 12 bit resolution = 0 - 4096 (2^12)
  // Initialize motor driver pins as outputs
  //pinMode(ENCA1, INPUT);
  //pinMode(ENCB1, INPUT);
  //pinMode(ENCA2, INPUT);
  //pinMode(ENCB2, INPUT);
  //attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoderA1, RISING);
  //attachInterrupt(digitalPinToInterrupt(ENCA2), readEncoderA2, RISING);
  pinMode(rsensor, INPUT);
  pinMode(lsensor, INPUT);

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
 if (strcmp(comparisonString,stringUp) == 0){
        DpadUp = true; 
        Serial.println("DpadUp esajks");
    }  
    if (strcmp(comparisonString,stringDown) == 0){
        DpadDown = true; 
        Serial.println("DpadUp esajks");
    }  
    if (strcmp(comparisonString,stringLeft) == 0){
        DpadLeft = true; 
        Serial.println("DpadUp esajks");
    }  
    if (strcmp(comparisonString,stringRight) == 0){
        DpadRight = true; 
        Serial.println("DpadUp esajks");
    }  
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
    
 
 
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}

void loop1(){ //This Runs on Core 2 and performs all inputs and outputs
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

   //Serial.println("You are in idle mode");//this line may be removed for final version
   digitalWrite(LED_BUILTIN, LOW); // LED is off for idle mode
    // No further action required
  }
  else if (current_mode == AUTO_MODE){
    //Serial.println("You are in auto mode");//this line may be removed for final version
    digitalWrite(LED_BUILTIN, LOW); // LED is off for auto mode
    // Write additional commands for autonomous mode
    //CAUTION: YOU CANNOT PRESS ANY BUTTONS WHILE IN AUTO MODE UNLESS YOU PASS THE GATE (in this case, press B to go to manual mode)
    leftVal = analogRead(lsensor);
    rightVal = analogRead(rsensor);
    leftVal = map(leftVal,0,4096,0,1024);
    rightVal = map(rightVal,0,4096,0,1024);
    Serial.print(leftVal); 
      Serial.print("     ");
    Serial.println(rightVal);
    // If both sensors detect white, move forward.
    if (leftVal < whiteLevel && rightVal < whiteLevel) {
      // Add your code here to move forward
      setMotor(1, 255, PWMA, AI1, AI2);
      setMotor(1, 255, PWMB, BI1, BI2);
    }
    // If left sensor detects black (right sensor white), turn right.
    else if (leftVal > blackLevel && rightVal < whiteLevel) {
      // Add your code here to turn right
      setMotor(-1, 255, PWMA, AI1, AI2);
      setMotor(1, 255, PWMB, BI1, BI2);
    }
    // If right sensor detects black (left sensor white), turn left.
    else if (leftVal < whiteLevel && rightVal > blackLevel) {
      // Add your code here to turn left
      setMotor(1, 255, PWMA, AI1, AI2);
      setMotor(-1, 255, PWMB, BI1, BI2);
    }
    // If both sensors detect black, you might want to stop or take a special action.
    else if (leftVal > blackLevel && rightVal > blackLevel) {
      // Add your code here for both sensors detecting black

      delay(2000);
      setMotor(0, 255, PWMA, AI1, AI2);
      setMotor(0, 255, PWMB, BI1, BI2);
      current_mode == MANUAL_MODE;
    }
}
  else if (current_mode == MANUAL_MODE){
    digitalWrite(LED_BUILTIN,1);
   if(DpadLeft){
      clawDeg += 10; 
     
      myservo1.write(clawDeg);
      DpadLeft = false; 
   
    }
    if(DpadRight == true){
      clawDeg -= 10; 
     
      myservo1.write(clawDeg);
      DpadRight = false; 


    }
  
    // Write additional commands for manual mode
    if(DpadUp){
      armDeg -= 5; 
      if(armDeg < 0){
        armDeg = 0; 
      }
      
      myservo2.write(armDeg);
      DpadUp = false; 
      Serial.println("DpadUp: armDeg Value = "); 
      Serial.print(armDeg);
    }
    if(DpadDown == true){
      armDeg += 5; 
      
      if(armDeg > 180){
        armDeg = 180; 
      };
      myservo2.write(armDeg);
      DpadDown = false; 
      Serial.println("DpadDown: armDeg Value = "); 
      Serial.print(armDeg); 
    }
   // int gripPos = map(valueRt,0,255,0,180); 
   // myservo2.write(gripPos);

    //Forward and Backwards
    int dir = 1;
    if(valueLy < 0) 
      dir = -dir; 
         
    //Right and Left Turning
    int turnDir = -1;
    if(valueRx < 0) 
      turnDir = -turnDir;

    if (abs(valueLy) < 150 && abs(valueLy) >= 100)
      valueLy = 150;
    else if(abs(valueLy) < 100)
      valueLy = 0;

    if (abs(valueRx) < 150 && abs(valueRx) >= 100)
      valueRx = 150;
    else if(abs(valueRx) < 100)
      valueRx = 0;

    if (abs(valueRx) == 0){
      setMotor(dir, abs(valueLy), PWMA, AI1, AI2);
      setMotor(dir, abs(valueLy), PWMB, BI1, BI2);
    }
    else if (abs(valueLy) == 0){  
      setMotor(turnDir, abs(valueRx), PWMA, AI1, AI2);
      setMotor(-turnDir, abs(valueRx), PWMB, BI1, BI2);
    }
    else{
      setMotor(0, 0, PWMA, AI1, AI2);
      setMotor(0, 0, PWMB, BI1, BI2);
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

/*void readEncoderA1() {
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
}*/
