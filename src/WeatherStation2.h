#ifndef _WEATHER_STATION_2_H_
#define _WEATHER_STATION_2_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "Version.h"
#include "ArduinoSketchBase.h"

class WeatherStation2 : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      float temperature;
      int humidity;
      int pressure;

    protected:
      void Setup() override;
      void Loop() override;

    public:
      WeatherStation2();
      void Run();

};

#endif