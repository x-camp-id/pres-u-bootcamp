#define LED_RED 27
#define LED_GREEN 26
#define LED_BLUE 25
#define BUTTON 4

int state = 0;

void setup() {
  // Set LED pins as output and button pin as input
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUTTON, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("System ready.");
}

void loop() {
  // Check if button is pressed (active high)
  if (digitalRead(BUTTON) == HIGH) {
    state++; // increment state counter
    if (state > 3) state = 1; // reset state after 3
    Serial.print("Button pressed. State: ");
    Serial.println(state);
    delay(300); // debounce delay to avoid multiple triggers
  }

  // Turn on/off the corresponding LED based on state
  if (state == 1) {
    digitalWrite(LED_RED, HIGH);

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
  } else if (state == 2) {
    digitalWrite(LED_GREEN, HIGH);

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);
  } else {
    digitalWrite(LED_BLUE, HIGH);

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
  } 
}