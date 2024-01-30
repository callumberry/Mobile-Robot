const int ENCA = 17;
const int ENCB = 16;  

const int PWMA = 21;
const int AI2 = 20;
const int AI1 = 19;
const int STBY = 18;

int pos = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(1000); 
  digitalWrite(LED_BUILTIN, LOW); 

  Serial.begin(115200);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

  pinMode(PWMA, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); 
}

void loop() {

  setMotor(1, 100, PWMA, AI1, AI2);
  delay(1000);
  Serial.println(pos);
  setMotor(0, 100, PWMA, AI1, AI2);
  delay(1000);
  Serial.println(pos);
  setMotor(-1, 100, PWMA, AI1, AI2);
  delay(1000);
  Serial.println(pos);

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

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b>0){
    pos++;
  }
  else{
    pos--;
  }
}
