/*
 * Project WeatherBuddy
 * Description: A weather interface for the coffee table.
 * Author: Graham Plata
 * Date: March 31, 2019
 */

// This #include statement was automatically added by the Particle IDE.
#include <ITEADLIB_Nextion.h>

USARTSerial &nexSerial = Serial1;

// Index Page Nexobject [page id:0,component id:1, component name: "b0"]
NexText textLow(0, 3, "textLow");
NexText textHigh(0, 4, "textHigh");
NexText textTemp(0, 2, "textTemp");
NexText textLocation(0, 5, "textLocation");

int temperatureLow = 0;
int temperatureHigh = 0;
int temperature = 0;
float humidity = 0;

char buffer[100] = {0};

// Put initialization like pinMode and begin functions here.
void setup(void) {
  nexInit();                        // Set the baudrate which is for debug and communicate with Nextion screen.
  Time.zone(-5);                    // Set Time Zone to EST
}

// loop() runs over and over again, as quickly as it can execute.
void loop(void) {
  // The core of your code will likely live here.
}

String getTime() {
  String timeNow = Time.format(Time.now(), TIME_FORMAT_DEFAULT);
  timeNow = timeNow.substring(11, timeNow.length() - 6);
  return " " + timeNow;
}