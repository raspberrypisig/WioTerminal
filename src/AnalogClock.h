#ifndef _ANALOG_CLOCK_H
#define _ANALOG_CLOCK_H

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include "rpcWiFi.h"
#include <Wire.h>
#include "RTC_SAMD51.h"
#include "DateTime.h"

//#define TFT_GREY 0x5AEB



class AnalogClock : public ArduinoSketchBase {
static constexpr char *analogclock_ssid = "mycrib"; 
static constexpr char *analogclock_password = "peachspeak38"; 
static constexpr char *analogclock_timeServer = "time.nist.gov";
static constexpr int NTP_PACKET_SIZE = 48;

    private: 
      TFT_eSPI tft;
float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=120, osy=120, omx=120, omy=120, ohx=120, ohy=120;  // Saved H, M, S x & y coords
uint16_t x0=0, x1=0, yy0=0, yy1=0;
uint32_t targetTime = 0;                    // for next 1 second timeout

uint8_t conv2d(const char* p);
uint8_t hh=conv2d(__TIME__), mm=conv2d(__TIME__+3), ss=conv2d(__TIME__+6);  // Get H, M, S from compile time

boolean initial = 1;     

unsigned int localPort = 2390;






byte packetBuffer[NTP_PACKET_SIZE];

void printWifiStatus();

// declare a time object

DateTime now;

 

// define WiFI client

WiFiClient client;

 

//The udp library class

WiFiUDP udp;

 

// localtime

unsigned long devicetime;

 

RTC_SAMD51 rtc;

 

// for use by the Adafuit RTClib library

char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

 void connectToWiFi(const char* ssid, const char* pwd);
 unsigned long sendNTPpacket(const char* address);
 unsigned long getNTPtime();

    protected:
      void Setup() override;
      void Loop() override;

    public:
      AnalogClock();
      void Run();

};

#endif