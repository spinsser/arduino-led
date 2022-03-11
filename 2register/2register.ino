int clockPin = 12;
int clearPin = 8;
int dataPin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(clockPin, OUTPUT);
  pinMode(clearPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(clearPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 256; i++){
    
    //digitalWrite(clearPin, LOW);
    //digitalWrite(clearPin, HIGH);

    digitalWrite(dataPin, HIGH);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    //shiftOut(dataPin, clockPin, MSBFIRST, i);
    //delay(25);
    //shiftOut(dataPin, clockPin, MSBFIRST, i);
    delay(1000);
  }
}
