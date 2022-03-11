int dataPin = 3;
int clockPin = 4;

int numbers[] = {0b00000010, 0b10011110, 0b00100100, 0b00001100, 0b10011000, 0b01001000, 0b01000000, 0b00011110, 0b00000000, 0b00001000};
int segNull = 0b11111110;
int segL = 0b11100010;
int segH = 0b10010000;
int segE = 0b01100000;
int segT = 0b11100000;

int number = 0;
unsigned long mDelay = 1000;
unsigned long mSec = millis();

int D1 = 8;
int D2 = 9;
int D3 = 10;
int D4 = 11;

int dispDelay = 5;

void setup() {
  Serial.begin(57600);
  // put your setup code here, to run once:
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int modes[] = {'I', 'L', 'H', 'E', 'T'};

  displayNumber(number, modes[number % 5]);

  if (millis() > mSec + mDelay) {
    number++;
    Serial.println(millis());
    mSec = millis();
  }

}

void displayNumber(int value, char mode) {
  // value: integer value to be printed (0 - 999)
  // mode: I - Input, L - Single LED, H - Route, E - Error, T - Test Mode
  int modeD = 0;
  if (value > 0 && value < 1000) {
    switch (mode) {
      case 'I':
        modeD = segNull;
        break;

      case 'L':
        modeD = segL;
        break;

      case 'H':
        modeD = segH;
        break;

      case 'E':
        modeD = segE;
        break;

      case 'T':
        modeD = segT;
        break;
    }
    int list[] = {0, 0, 0};
    int tempVal = value;

    for (int i = 2; i >= 0; i--) {
      list[2 - i] = tempVal / power(10, i);
      tempVal = tempVal % power(10, i);
    }

    digitalWrite(D1, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, modeD);
    digitalWrite(D1, HIGH);
    delay(dispDelay);
    digitalWrite(D1, LOW);

    digitalWrite(D2, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, numbers[list[0]]);
    digitalWrite(D2, HIGH);
    delay(dispDelay);
    digitalWrite(D2, LOW);

    digitalWrite(D3, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, numbers[list[1]]);
    digitalWrite(D3, HIGH);
    delay(dispDelay);
    digitalWrite(D3, LOW);

    digitalWrite(D4, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, numbers[list[2]]);
    digitalWrite(D4, HIGH);
    delay(dispDelay);
    digitalWrite(D4, LOW);
  }
}

int power(int b, int p) {
  int output = 1;
  for (int i = 0; i < p; i++) {
    output = output * b;
  }
  return output;
}
