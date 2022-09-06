int led = 0;     // LED pin
int led2 = 2;     // LED pin

int button = 3; // push button is connected
int button2 = 1;

void setup() {
  pinMode(led, OUTPUT);   // declare LED as output
  pinMode(button, INPUT); // declare push button as input
  pinMode(led2, OUTPUT);   // declare LED as output
  pinMode(button2, INPUT); // declare push button as input
  digitalWrite(led, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(button, LOW);
  digitalWrite(button2, LOW);



}

void loop() {
  if (digitalRead(button) == HIGH) {
    digitalWrite(led, HIGH);
  }
  else if (digitalRead(button2) == HIGH) {
    digitalWrite(led2, HIGH);
  }
  else if (digitalRead(button) == LOW and digitalRead(button2) == LOW) {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
  }
  else if (digitalRead(button) == HIGH and digitalRead(button2) == HIGH) {
  digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
  }
}
