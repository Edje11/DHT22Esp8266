
#include <PietteTech_DHT.h> //https://github.com/chaeplin/PietteTech_DHT-8266

// Config
#define DHTPIN 4 // what data pin DHT is connected to
#define DHTPOWERPIN 5 //power supply of the DHT22 is connected to pin 5 so we can switch it complete off to save energy (and reset if needed)
#define DHTTYPE AM2302 // DHT Type
#define LEDPIN 10 // Led pin
#define VOLTDIVIDER 4.39 //

// declaration
void dht_wrapper(); // must be declared before the lib initialization

// Lib instantiate
PietteTech_DHT DHT(DHTPIN, DHTTYPE, dht_wrapper);

// globals
bool bDHTstarted; // flag to indicate we started acquisition
unsigned long startMills;
float humidity = 0;
float temperature = 0;
int batvolt=0;


// This wrapper is in charge of calling
// must be defined like this for the lib work
void dht_wrapper() {
DHT.isrCallback();
}


void setup(void)
{
pinMode(DHTPOWERPIN, OUTPUT);  
digitalWrite(DHTPOWERPIN, HIGH);
pinMode(LEDPIN, OUTPUT);
digitalWrite(LEDPIN, LOW);
Serial.begin(115200);
}


void loop(void)
{
int acquireresult;
delay(2000);
DHT.acquireAndWait(100);
delay(2000);
acquireresult = DHT.acquireAndWait(100); // read twice as the first result is cached from last time. suggested by @chaeplin
if ( acquireresult == 0 ) {
temperature = DHT.getCelsius();
humidity = DHT.getHumidity();
batvolt= analogRead(A0)* VOLTDIVIDER;
Serial.println();
Serial.print("Humidity (%): ");
Serial.println(humidity, 2);
Serial.print("Temperature (°C): ");
Serial.println(temperature, 2);
Serial.print("Battery (mV): ");
Serial.println(batvolt);
 delay(10);
}

Serial.print("Going to sleep");
digitalWrite(DHTPOWERPIN, LOW); //Turn off DHT22
digitalWrite(LEDPIN, HIGH); //Turn off LED
delay(250);
//ESP.deepSleep(5 * 60 * 1000 * 1000);
ESP.deepSleep(15 * 1000000);   // deepSleep time is defined in microseconds. Multiply seconds by 1e6 
delay(1000);
}

