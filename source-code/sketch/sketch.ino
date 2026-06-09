#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>

// ---------------- WIFI ----------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ---------------- MQTT ----------------
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// ---------------- DHT22 ----------------
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN,  DHTTYPE);

// ---------------- BMP180 ----------------
Adafruit_BMP085 bmp;

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- CALLBACK FUNCTION ----------------
void callback(char* topic, byte* message, unsigned int length) {

  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  String receivedMessage;

  for (int i = 0; i < length; i++) {
    receivedMessage += (char)message[i];
  }

  Serial.print("Message: ");
  Serial.println(receivedMessage);
}

// ---------------- WIFI SETUP ----------------
void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
}

// ---------------- MQTT RECONNECT ----------------
void reconnect() {

  while (!client.connected()) {

    Serial.print("Connecting to MQTT...");

    String clientId = "ESP32_WeatherStation";

    if (client.connect(clientId.c_str())) {

      Serial.println("Connected");

      client.subscribe("weather/control");

    } else {

      Serial.print("Failed, rc=");
      Serial.print(client.state());

      delay(2000);
    }
  }
}

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);

  // DHT22 Setup
  dht.begin();

  // BMP180 Setup
  bmp.begin();

  // LCD Setup
  lcd.init();
  lcd.backlight();

  // WiFi Setup
  setup_wifi();

  // MQTT Setup
  client.setServer(mqtt_server, 1883);

  // Callback Registration
  client.setCallback(callback);

  lcd.setCursor(0, 0);
  lcd.print("Weather System");

  delay(2000);
  lcd.clear();
}

// ---------------- LOOP ----------------
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  // -------- READ DHT22 --------

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bmp.readPressure() / 100.0;

  if (isnan(temperature) || isnan(humidity)) {

  Serial.println("DHT Sensor Error!");
  return;
}

  // -------- READ BMP180 --------
 // float pressure = bmp.readPressure() / 100.0;

  // -------- SERIAL MONITOR --------
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  // -------- LCD DISPLAY --------
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C ");

  lcd.print("H:");
  lcd.print(humidity);

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(pressure);
  lcd.print("hPa");

  // -------- MQTT PUBLISH --------
  String tempString = String(temperature);
  String humString = String(humidity);
  String pressureString = String(pressure);

  client.publish("weather/temp", tempString.c_str());

  client.publish("weather/humidity", humString.c_str());

  client.publish("weather/pressure", pressureString.c_str());

  delay(5000);
}
