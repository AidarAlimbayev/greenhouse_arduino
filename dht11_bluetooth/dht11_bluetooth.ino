#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("BlueCore Tech Temperature and Humidity");

  dht.begin();
}

void loop() {
  // Give it time to calibrate
  delay(500);

  
  float h = dht.readHumidity();
  // Read Celsius
  float t = dht.readTemperature();
  // Read Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check errors
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.println("Humidity: ");
  Serial.print(h);
  Serial.println(" %.");
  Serial.println("  ");
  Serial.println("Temperature: ");
  Serial.print(t);
  Serial.println(" Degrees ");
}
