/*
 * Project WeatherBuddy
 * Description: A weather interface for the coffee table.
 * Author: Graham Plata
 * Date: March 31, 2019
 */

// This #include statement was automatically added by the Particle IDE.
#include <ITEADLIB_Nextion.h>

// App Version Constant
#define APP_VERSION "v0.3"

USARTSerial &nexSerial = Serial1;

// Nextion Objects and Pages
// Page: 0 Nexobjects [page id:0,component id:1, component name: "helloText"]
NexPage indexPage = NexPage(0, 0, "Weather");
NexPage loadingPage = NexPage(1, 0, "Loading");
// Components
NexText textLow(0, 3, "textLow");
NexText textHigh(0, 4, "textHigh");
NexText textTemp(0, 2, "textTemp");
NexText textLocation(0, 5, "textLocation");
NexText textTime(0, 6, "time");
NexText textHumidity(0, 11, "textHumidity");
NexText textWind(0, 14, "textWind");

// Nextion Touch events
NexTouch *nex_Listen_List[] = {&textTemp, NULL};

// Global Variables
int currentTime = 0;
double temperature = 0.0;
int temperatureMax = 0;
int temperatureMin = 0;
int humidity = 0;
int windSpeed = 0;

// Utility Buffer
char buffer[100] = {0};

// Device State
String deviceID;
bool demoMode = false;
bool connectToCloud = false;

// GPIO Variables
int led = D7;

// Initialization function: Runs once on Boot
void setup(void)
{
  // Set the baudrate which is for debug and communicate with Nextion screen.
  dbSerial.begin(9600);
  nexInit();                                  // Begin Nextion connection
  textTemp.attachPop(temperaturePopCallback); // Attach event listener to refresh variables

  // DateTime configurations
  Time.zone(-5);

  // Setting port OUTPUTs
  pinMode(led, OUTPUT);

  // Initializing port initial state
  digitalWrite(led, LOW);

  // Register Particle Cloud variables, functions and subscriptions
  registerWithCloud();

  // set initial button and text states
  defaultState();
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
    Particle.publish("get_weather", data, PRIVATE);
    delay(60000 * 2); // ask every two minutes
  }

  nexLoop(nex_Listen_List);
}

// clears all the past variables and sets defaults values
void defaultState()
{
  memset(buffer, 0, sizeof(buffer));
  itoa(temperature, buffer, 10);
  textTemp.setText(buffer);
  textLow.setText(buffer);
  textHigh.setText(buffer);
  snprintf(buffer, sizeof(buffer), APP_VERSION);
  textLocation.setText(buffer);
}

// Register Particle Cloud variables, functions and subscriptions
void registerWithCloud()
{
  deviceID = System.deviceID();
  Particle.publish("Version", APP_VERSION);
  Particle.publish("Device ID", deviceID);
  Particle.publish("Status", "Online");

  Particle.variable("currentTime", currentTime);
  Particle.variable("temperature", temperature);
  Particle.variable("temperatureMax", temperatureMax);
  Particle.variable("temperatureMin", temperatureMin);
  Particle.variable("humidity", humidity);
  Particle.variable("windSpeed", windSpeed);

  Particle.function("demoMode", demoModeFunc);
  Particle.subscribe("hook-response/get_weather", gotWeatherData, MY_DEVICES);
}

// Demo Mode
void runDemo()
{
  String temperatureLow = String(random(60, 80));
  String temperatureHigh = String(random(60, 80));
  String temp = String(random(60, 80));
  String temp2 = String(random(60, 80));
  String temp3 = String(random(60, 80));
  textTemp.setText(temp);
  textLow.setText(temperatureLow);
  textHigh.setText(temperatureHigh);
  textHumidity.setText(temp2);
  textWind.setText(temp3);
}

// Test Function
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

// Request New Data from Darksky
void temperaturePopCallback(void *ptr)
{
  String data = String(10);
  Serial.println("");
  Serial.println("-------------------");
  Serial.println("Requesting Weather!");
  Particle.publish("get_weather", data, PRIVATE);
}

// Parse and Set new data
void gotWeatherData(const char *name, const char *data)
{
  String str = String(data);
  char strBuffer[500] = "";
  str.toCharArray(strBuffer, 500);

  temperature = atof(strtok(strBuffer, "~"));
  currentTime = atoi(strtok(NULL, "~"));
  humidity = 100 * atof(strtok(NULL, "~"));
  windSpeed = atof(strtok(NULL, "~"));
  temperatureMax = atoi(strtok(NULL, "~"));
  temperatureMin = atoi(strtok(NULL, "~"));

  textTemp.setText(String(temperature));
  textHumidity.setText(String(humidity));
  textWind.setText(String(windSpeed));
  textLow.setText(String(temperatureMin));
  textHigh.setText(String(temperatureMax));
  textTime.setText(String(Time.format(currentTime)));
}
