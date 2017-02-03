/* the purpose of this sketch is to show two different ways
   of achieving pulse width modulation on the arduino

   method one uses analogWrite(), which takes an input x of 0-255 (off-brightest)
   and in periods of 2 ms will have the LED on for (x*100/255)% of the time
   (pretty sure standard period is 2 ms, but not absolutely sure)
   which, because it is occurring too fast for human eyes to register,
   will appear as a constant brightness

   the second method uses digitalWrite() with a delay function to achieve the same result
   thinking of adding in a button that will change the delay values

   we will control the analogWrite()'s input x using a potentiometer
   to add some interactive fun for the kiddo's
*/

const int POT_PIN = A0;
const int BUTTON_PIN = 3;
const int A_PIN = 11;
const int D_PIN = 12;

int lastButtonState = 1;
int count = 0;
int digiOn = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(A_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);
}

void loop() {
  double brightness = analogRead(A0) / 4.02;
  analogWrite(A_PIN, brightness);

  digitalWrite(D_PIN, HIGH); // periods of 10 ms
  delay(digiOn);
  digitalWrite(D_PIN, LOW);
  delay(10 - digiOn);

  if (lastButtonState == 1 && digitalRead(BUTTON_PIN) == 0) {
    lastButtonState = 0;
    digiOn++;
    if (digiOn > 10) {
      digiOn = 0;
    }
  }

  if (lastButtonState == 0 && digitalRead(BUTTON_PIN) == 1) {
    lastButtonState = 1;
  }

  count++;
  if (count % 50 == 0) {
    Serial.println(digiOn);
    Serial.println(brightness);
  }

}

