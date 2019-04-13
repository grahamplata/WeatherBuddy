/*
 * Project WeatherBuddy
 * Description: A weather interface for the coffee table.
 * Author: Graham Plata
 * Date: March 31, 2019
 */

// This #include statement was automatically added by the Particle IDE.
#include <ITEADLIB_Nextion.h>

// App Version Constant
#define APP_VERSION "v0.1"

USARTSerial &nexSerial = Serial1;

// Nextion Objects and Pages
// Page: 0 Nexobjects [page id:0,component id:1, component name: "helloText"]
// Pages
NexPage indexPage = NexPage(0, 0, "Weather");
NexPage loadingPage = NexPage(1, 0, "Loading");
// Component
NexText textLow(0, 3, "textLow");
NexText textHigh(0, 4, "textHigh");
NexText textTemp(0, 2, "textTemp");
NexText textLocation(0, 5, "textLocation");

// Global temperature Variables
int temperatureLow = 0;
int temperatureHigh = 0;
int temperature = 0;
char *message = "Weather Buddy v0.1";

// Utility Buffer
char buffer[100] = {0};

// State
String deviceID;
bool demoMode = false;
bool connectToCloud = false;

// Touch events
NexTouch *nex_Listen_List[] =
    {
        // &textLow,
        // &textHigh,
        // &textTemp,
        // NULL
};

// GPIO Variables
int led = D7;

// Initialization function: Runs once on Boot
void setup(void)
{
  // Set the baudrate which is for debug and communicate with Nextion screen.
  dbSerial.begin(9600);
  nexInit(); // Begin connection
  loadingPage.show();

  deviceID = System.deviceID();
  Particle.publish("Version", APP_VERSION);
  Particle.publish("Device ID", deviceID);
  Particle.publish("Status", "Online");

  // DateTime configurations
  Time.zone(-5);

  // Setting port OUTPUTs
  pinMode(led, OUTPUT);

  // Initializing port initial state
  digitalWrite(led, LOW);

  // Register Particle Cloud variables and functions
  registerCloudVariables();
  registerCloudFunctions();
  Particle.subscribe("hook-response/get_weather", gotWeatherData, MY_DEVICES);

  indexPage.show();
  defaultState(); // set initial button and text states
}

// loop() runs over and over again, as quickly as it can execute.
void loop(void)
{
  String data = String(10);

  if (demoMode == true)
  {
    runDemo();
    delay(3000);
  }
  else
  {
    Serial.println("");
    Serial.println("-------------------");
    Serial.println("Requesting Weather!");
    delay(60000 * 5);
  }

  nexLoop(nex_Listen_List);
}

// clears all the past variables and sets defaults values
void defaultState()
{
  // Set Ints
  memset(buffer, 0, sizeof(buffer));
  itoa(temperature, buffer, 10);
  textTemp.setText(buffer);
  textLow.setText(buffer);
  textHigh.setText(buffer);
  // String
  snprintf(buffer, sizeof(buffer), message);
  textLocation.setText(buffer);
}

// Setup Functions
// Registers Variables with the Particle Cloud
void registerCloudVariables()
{
  Particle.variable("temperatureLow", &temperatureLow, INT);
  Particle.variable("temperatureHigh", &temperatureHigh, INT);
  Particle.variable("temperature", &temperature, INT);
  Particle.variable("message", message, STRING);
}

void registerCloudFunctions()
{
  Particle.function("demoMode", demoModeFunc);
}

// Demo Function
void runDemo()
{
  String temperatureLow = String(random(60, 80));
  String temperatureHigh = String(random(60, 80));
  String temp = String(random(60, 80));
  textTemp.setText(temp);
  textLow.setText(temperatureLow);
  textHigh.setText(temperatureHigh);
}

// test function
int demoModeFunc(String command)
{
  if (command == "on")
  {
    demoMode = true;
    digitalWrite(led, HIGH);
    return 0;
  }
  else
  {
    demoMode = false;
    digitalWrite(led, LOW);
    return 0;
  }
}

void gotWeatherData(const char *name, const char *data)
{
  Serial.print("Got Weather Data!\n");
  String str = String(data);
  char strBuffer[500] = "";
  str.toCharArray(strBuffer, 500);
  int currentTemperature = atoi(strtok(strBuffer, "\"~"));
  int temperatureMax = atoi(strtok(NULL, "~"));
  int temperatureMin = atoi(strtok(NULL, "~"));

  Serial.print("CurrentTemperature: ");
  Serial.println(currentTemperature);
  Serial.print("temperatureMax: ");
  Serial.println(temperatureMax);
  Serial.print("temperatureMin: ");
  Serial.println(temperatureMin);

  textTemp.setText(String(currentTemperature));
  textLow.setText(String(temperatureMin));
  textHigh.setText(String(temperatureMax));
}
