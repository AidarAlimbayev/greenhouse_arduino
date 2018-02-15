#include <DHT.h>
#include <DHT_U.h>

// определение пинов 
#define relay_light  6                        
#define relay_fan  7                        
#define relay_pump  8                        
#define relay_heater  9
#define DHTPIN 11

DHT dht(DHTPIN, DHT11);

char incomingChar;
String fullString = "";
int temp_value;

// объявление переменных датчиков
float gnd_humidity = 0;
float air_hum = 0;
float air_temp = 0;
int co2_sensor = 0;

void setup()
{    
  Serial.begin(9600); // Инициализация входного порта с последовательного порта
  dht.begin();        // Инициализация температурного датчика
  
// Инициализация выходных портов для реле
  pinMode(relay_light, OUTPUT);       
  pinMode(relay_fan, OUTPUT);
  pinMode(relay_pump, OUTPUT);
  pinMode(relay_heater, OUTPUT);
  
// Инициализация датчиков
  pinMode(co2_sensor, INPUT);   // анализатор воздуха
}

 void loop()
{
  // считывание температуры и влажности
  air_temp = dht.readTemperature();
  air_hum = dht.readHumidity();

  if(isnan(air_temp) || isnan(air_hum)){
    Serial.println("TEMP and HUM unavailable");
  return;
  }

  Serial.print(" Temperature:");
  Serial.print(air_temp);
  Serial.print(" %\t");
  Serial.print("Humidity:");
  Serial.print("air_hum");
  Serial.print(" *C");

  if(Serial.available() > 0)
  {
    while(Serial.available()!=0)
    {
      incomingChar=Serial.read();
      delay(2); // задержка 2мс. нужна, чтобы сериал порт успел принять все символы.
       fullString += incomingChar;
    }
  }

 // отработка внешних команд
  if(fullString == "light_on"){
      digitalWrite(relay_light,HIGH);           // Turns ON Relays 1
  }
  if(fullString == "light_off"){
      digitalWrite(relay_light,LOW);             // Turns Relay Off
  }
  if(fullString == "fan_on"){
      digitalWrite(relay_fan,HIGH);           // Turns ON Relays 1
  }
  if(fullString == "fan_off"){
      digitalWrite(relay_fan,LOW);           // Turns ON Relays 1
  }
  if(fullString == "pump_on"){
      digitalWrite(relay_pump,HIGH);           // Turns ON Relays 1
  }
  if(fullString == "pump_off"){
      digitalWrite(relay_pump,LOW);           // Turns ON Relays 1
  }
  if(fullString == "heater_on"){
     digitalWrite(relay_heater,HIGH);           // Turns ON Relays 1
  }
  if(fullString == "heater_off"){
      digitalWrite(relay_heater,LOW);           // Turns ON Relays 1
  }
  fullString = "";
}

