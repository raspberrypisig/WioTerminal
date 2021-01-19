#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "Version.h"

class WeatherStation1 {
    private: 
      TFT_eSPI tft;
      float temperature;
      int humidity;
      int pressure;

    public:
      WeatherStation1();
      void Run();
      void Setup();
      void Loop();
};