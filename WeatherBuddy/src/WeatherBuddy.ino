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

float temperatureLow = 0;
float temperatureHigh = 0;
float temperature = 0;
char *message = "Weather Buddy v0.1";

char buffer[100] = {0};

// Touch events to watch for.
NexTouch *nex_Listen_List[] = 
{
    // &textLow,
    // &textHigh,
    // &textTemp,
    // NULL
};

// GPIO Variables
int led = D7;

void setup(void) {
   // Initialization function
   // Set the baudrate which is for debug and communicate with Nextion screen.
   
   dbSerial.begin(9600);
   nexInit();
   
   // Nextion Buttons and text
   // set initial text states
    defaultState();
    

   // DateTime configurations
   Time.zone(-5);
   
   // Setting port OUTPUT
   pinMode(led, OUTPUT);
   
   // Initializing port initial state
   digitalWrite(led, LOW);

}

// loop() runs over and over again, as quickly as it can execute.
void loop(void) {
    // The core of your code will likely live here.
    nexLoop(nex_Listen_List);
}

// clears all the past variables and sets defaults values
void defaultState() {
    memset(buffer, 0, sizeof(buffer)); // this only CLEARS the buffer
    itoa(temperature, buffer, 10); // this converts the numeric data into string and stores in buffer
    textTemp.setText(buffer); // only after both of the above you can send it to the display
    textLow.setText(buffer); // only after both of the above you can send it to the display
    textHigh.setText(buffer); // only after both of the above you can send it to the display
    snprintf(buffer, sizeof(buffer), message);
    textLocation.setText(buffer); // only after both of the above you can send it to the display

}