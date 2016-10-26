
#include "DHT.h"  //https://github.com/adafruit/DHT-sensor-library

// Config
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN 4 // what data pin DHT is connected to
#define DHTPOWERPIN 5 //power supply of the DHT22 is connected to pin 5 so we can switch it complete off to save energy (and reset if needed)
#define LEDPIN 13 // Led pin
#define VOLTDIVIDER 4.39  //


// Lib instance 
DHT dht(DHTPIN, DHTTYPE);

// globals
bool bDHTstarted; // flag to indicate we started acquisition
unsigned long startMills;
float humidity = 0;
float temperature = 0;
int batvolt=0;


void setup(void)
{
pinMode(DHTPOWERPIN, OUTPUT);  
digitalWrite(DHTPOWERPIN, HIGH);
pinMode(LEDPIN, OUTPUT);
digitalWrite(LEDPIN, LOW);
Serial.begin(115200);
dht.begin();
}


void loop(void)
{
 // Wait a few seconds between measurements. Reading temperature or humidity takes about 250 milliseconds! Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
delay(2000);
temperature = dht.readTemperature();
humidity = dht.readHumidity();
batvolt= analogRead(A0)* VOLTDIVIDER;

// Check if any reads failed and exit early (to try again).
if (isnan(humidity) || isnan(temperature)){
 Serial.println("Failed to read from DHT sensor!");
    return;
  }
Serial.println();
Serial.print("Humidity (%): ");
Serial.println(humidity, 2);
Serial.print("Temperature (�C): ");
Serial.println(temperature, 2);
Serial.print("Battery (mV): ");
Serial.println(batvolt);


Serial.print("Going to sleep");
digitalWrite(DHTPOWERPIN, LOW); //Turn off DHT22
digitalWrite(LEDPIN, HIGH); //Turn off LED
delay(250);
ESP.deepSleep(15 * 1000000);   // deepSleep time is defined in microseconds. Multiply seconds by 1e6 
delay(1000);
}

