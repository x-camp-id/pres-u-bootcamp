#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Create LCD object at I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pin numbers
const int GAS_SENSOR_PIN = 34;  // Analog pin connected to gas sensor
const int LED_PIN = 26;         // Pin connected to LED
const int DHT_PIN = 14;         // Pin connected to DHT22
#define DHTTYPE DHT22            // Specify DHT type

// Initialize DHT sensor
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200); // Start serial communication

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();

  pinMode(LED_PIN, OUTPUT); // Set LED pin as output

  dht.begin(); // Start DHT sensor
}

void loop() {
  // Read values from sensors
  int gasValue = analogRead(GAS_SENSOR_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print to Serial Monitor
  Serial.printf("Gas: %d, Temp: %.1f, Hum: %.1f\n", gasValue, temperature, humidity);

  // Display data on LCD
  lcd.setCursor(0, 0);
  lcd.print("Gas:");
  lcd.print(gasValue);
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" H:");
  lcd.print(humidity);

  // Example condition: turn on LED if gas value is high
  if (gasValue > 500) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(2000); // Wait before next reading
}
