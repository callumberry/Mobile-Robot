const int ENCA1 = 17;
const int ENCB1 = 16;

const int ENCA2 = 14;
const int ENCB2 = 15;

const int PWMA = 21;
const int AI2 = 20;
const int AI1 = 19;
const int STBY = 18;

const int PWMB = 13;
const int BI2 = 11;
const int BI1 = 12;

int posA = 0;
int posB = 0;

long prevTime = 0;
float prevErrorA = 0;
float prevErrorB = 0;
float errorProportionalA = 0;
float errorProportionalB = 0;
float errorIntegralA = 0;
float errorIntegralB = 0;
float errorDerivativeA = 0;
float errorDerivativeB = 0;

const float Kp = 3;  // Proportional gain
const float Ki = 0.0007;  // Integral gain
const float Kd = 0.00001;  // Derivative gain

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
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

void loop() {
  int targetA = 250 * sin(prevTime / 1e6);
  int targetB = 250 * cos(prevTime / 1e6);

  PID(1, targetA, PWMA, AI1, AI2, posA, errorProportionalA, errorIntegralA, errorDerivativeA, prevErrorA);
  PID(1, targetB, PWMB, BI1, BI2, posB, errorProportionalB, errorIntegralB, errorDerivativeB, prevErrorB);

  Serial.print(targetA);
  Serial.print(" ");
  Serial.print(posA);
  Serial.print(" ");
  Serial.print(targetB);
  Serial.print(" ");
  Serial.println(posB);

  delay(100);
}

void PID(int dir, int target, int pwm, int i1, int i2, int &pos, float &errorProportional, float &errorIntegral, float &errorDerivative, float &prevError) {
  // Calculate time difference
  long currTime = micros();
  float timeDiff = ((float)(currTime - prevTime)) / 1.0e6;
  prevTime = currTime;

  // Calculate error
  int error = pos - target;

  // Calculate proportional, derivative, and integral error terms
  errorProportional = Kp * error;

  errorDerivative = Kd * ((error - prevError) / timeDiff);

  errorIntegral = Ki * (errorIntegral + error * timeDiff);

  float u = errorProportional + errorDerivative + errorIntegral;

  float power = fabs(u);
  if (power > 255) {
    power = 255;
  }

  if (u < 0) {
    dir = -dir;
  }

  analogWrite(pwm, power);
  if (dir == 1) {
    digitalWrite(i1, HIGH);
    digitalWrite(i2, LOW);
  } else if (dir == -1) {
    digitalWrite(i1, LOW);
    digitalWrite(i2, HIGH);
  } else {
    digitalWrite(i1, LOW);
    digitalWrite(i2, LOW);
  }
  prevError = error;
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
