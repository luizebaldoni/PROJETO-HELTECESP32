const int sensor1 = A0;
const int sensor2 = A1;

float valorSens1;
float valorSens1_old = 0;
float valorSens2;
float valorSens2_old = 0;
float randNumber;

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  Serial.begin(9600);
}

void loop() {
  ReadSensors();
}

void ReadSensors() {
  valorSens1 = analogRead(sensor1);
  valorSens2 = analogRead(sensor2);
  if (checkVariation())  {
    valorSens1_old = valorSens1;
    valorSens2_old = valorSens2;
    Serial.println("("+String(ValorSens1_Temp())+","+String(ValorSens2_Umid())+")");
    delay(2000);
  }
}

bool checkVariation() {
  if ((valorSens1) > (valorSens1_old + 5) || (valorSens1) < (valorSens1_old - 5) ||
      (valorSens2) > (valorSens2_old + 5) || (valorSens2) < (valorSens2_old - 5 )) {
    return (true);
  }
  else {
    return (false);
  }
}

float ValorSens1_Temp() {
  randNumber=random(1,4);
  return ((map(valorSens1, 0, 1023, 10, 40))/randNumber);
}

float ValorSens2_Umid() {
  randNumber=random(1,9);
  return ((map(valorSens2, 0, 1023, 1, 100))/randNumber); 
}
