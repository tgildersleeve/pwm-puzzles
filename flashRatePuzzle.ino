/* purpose of this sketch:
   kiddos get to plug a wire attached to an LED
   into different pins that provide voltage at different rates
   and they get to figure out which is which
   like a puzzle yo
*/

/*
   13: constantly on
   12: on 1000 ms, off 1000
   11: brightness goes low to high, then resets, at steady rate
   10: on 500 ms, off 1500
   9:  on 500 ms, off 500
   8:  randomized on and off periods
   7:  on 250 ms, off 250
   6:  on 1500 ms, off 500
   5:  brightness goes low to high to low at steady rate
   4:  button controls LED
   3:  potentiometer controls LED
*/

unsigned long count12 = 0;
bool on12 = 0;

unsigned long value11 = 0;
unsigned long count11 = 0;

unsigned long count10 = 0;
bool on10 = 0;

unsigned long count9 = 0;
bool on9 = 0;

unsigned long count8 = 0;
bool on8 = 0;

unsigned long count7 = 0;
bool on7 = 0;

unsigned long count6 = 0;
bool on6 = 0;

unsigned long value5 = 0;
unsigned long count5 = 0;
bool up5 = 0;

int lastButtonState = 1;
bool on4 = 1;

// would it be possible to cycle through creating these with a for loop?

void setup() {
  Serial.begin(9600);
  for (int i = 3; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  // PIN 13
  digitalWrite(13, HIGH); // constantly on

  // PIN 12
  if (millis() > count12) {
    if (on12) {
      digitalWrite(12, LOW);
      on12 = 0;
    }
    else {
      digitalWrite(12, HIGH);
      on12 = 1;
    }
    count12 += 1000;
  }


  // PIN 11
  count11++;
  if (count11 % 75 == 0) {
    value11++;
  }
  if (value11 > 255) {
    value11 = 0;
  }
  analogWrite(11, value11);

  // PIN 10
  if (millis() > count10) {
    if (on10) {
      digitalWrite(10, LOW);
      on10 = 0;
      count10 += 1500;
    }
    else {
      digitalWrite(10, HIGH);
      on10 = 1;
      count10 += 500;
    }
  }

  // PIN 9
  if (millis() > count9) {
    if (on9) {
      digitalWrite(9, LOW);
      on9 = 0;
      count9 += 500;
    }
    else {
      digitalWrite(9, HIGH);
      on9 = 1;
      count9 += 500;
    }
  }

  // PIN 8
  if (millis() > count8) {
    if (on8) {
      digitalWrite(8, LOW);
      on8 = 0;
      count8 += random(100, 2000);
    }
    else {
      digitalWrite(8, HIGH);
      on8 = 1;
      count8 += random(100, 2000);
    }
  }

  // PIN 7
  if (millis() > count7) {
    if (on7) {
      digitalWrite(7, LOW);
      on7 = 0;
      count7 += 250;
    }
    else {
      digitalWrite(7, HIGH);
      on7 = 1;
      count7 += 250;
    }
  }

  // PIN 6
  if (millis() > count6) {
    if (on6) {
      digitalWrite(6, LOW);
      on6 = 0;
      count6 += 500;
    }
    else {
      digitalWrite(6, HIGH);
      on6 = 1;
      count6 += 1500;
    }
  }

  // PIN 5
  count5++;
  if (count5 % 25 == 0) {
    if (up5) {
      value5++;
    }
    else {
      value5--;
    }
  }
  if (value5 == 255) {
    up5 = 0;
  }
  if (value5 == 0) {
    up5 = 1;
  }
  analogWrite(5, value5);

  // PIN 4
  if (digitalRead(2) == 0) {
    if (lastButtonState == 1) {
      lastButtonState = 0;
      if (on4) {
        digitalWrite(4, LOW);
        on4 = 0;
      }
      else {
        digitalWrite(4, HIGH);
        on4 = 1;
      }
    }
  }
  if (digitalRead(2) == 1) {
    lastButtonState = 1;
  }


  // PIN 3
  double brightness = analogRead(A0) / 4.02;
  analogWrite(3, brightness);

}

