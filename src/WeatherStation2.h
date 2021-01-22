#ifndef _WEATHER_STATION_2_H_
#define _WEATHER_STATION_2_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "Version.h"
#include "ArduinoSketchBase.h"

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
#define TFT_GREY 0x2104 // Dark grey 16 bit colour


class WeatherStation2 : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      float temperature;
      int humidity;
      int pressure;
      unsigned long current_millis;
      unsigned long previous_millis=0UL;
      enum class ProgramState { ShowTemp, ShowHumidity, ShowPressure  };
      ProgramState programState;
      int ringMeter(int value, int vmin, int vmax, int x, int y, int r, const char *units, byte scheme);
      unsigned int rainbow(byte value);

    protected:
      void Setup() override;
      void Loop() override;

    public:
      WeatherStation2();
      void Run();

};

#endif