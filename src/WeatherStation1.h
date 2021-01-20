#ifndef _WEATHER_STATION_1
#define _WEATHER_STATION_1

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "Version.h"
#include "ArduinoSketchBase.h"

class WeatherStation1 : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      float temperature;
      int humidity;
      int pressure;

    protected:
      void Setup() override;
      void Loop() override;

    public:
      WeatherStation1();
      void Run();

};

#endif