#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <Wire.h>

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pin numbers
const int GAS_SENSOR_PIN = 34;
const int LED_PIN = 26;
const int DHT_PIN = 14;
#define DHTTYPE DHT22

// WiFi and MQTT broker credentials
const char* ssid = "Wokwi-GUEST";  // Use Wokwi-GUEST for Wokwi simulation
const char* password = "";         // No password for Wokwi-GUEST
const char* mqtt_server = "broker.xdevelopment.my.id";
const char* mqtt_user = "pu_xcamp";
const char* mqtt_pass = "pu_xcamp";

// Topic definitions [Please replace 'group-xx' with your actual group number]
const char* subscribe_topic = "pres-u/group-xx/led_control";
const char* publish_gas_topic = "pres-u/group-xx/gas";
const char* publish_temp_topic = "pres-u/group-xx/temp";
const char* publish_hum_topic = "pres-u/group-xx/hum";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHTTYPE);

// MQTT callback function
void callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(message);

    // Control LED via MQTT message
    if (message == "ON") {
        digitalWrite(LED_PIN, HIGH);
    } else if (message == "OFF") {
        digitalWrite(LED_PIN, LOW);
    }
}

void setup() {
    Serial.begin(115200);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    delay(1000);
    lcd.clear();

    pinMode(LED_PIN, OUTPUT);
    dht.begin();

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void reconnect() {
    // Reconnect to MQTT broker
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
            Serial.println("connected");
            // Subscribe to topic controlling LED
            client.subscribe(subscribe_topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            delay(1000);
        }
    }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

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

    // Publish data to MQTT topics
    client.publish(publish_gas_topic, String(gasValue).c_str());
    client.publish(publish_temp_topic, String(temperature).c_str());
    client.publish(publish_hum_topic, String(humidity).c_str());

    delay(2000);
}