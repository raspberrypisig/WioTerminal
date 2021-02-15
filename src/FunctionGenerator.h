#ifndef _FUNCTION_GENERATOR_H_
#define _FUNCTION_GENERATOR_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include <Adafruit_ZeroDMA.h>
#include "Adafruit_ZeroTimer.h"

class FunctionGenerator : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      Adafruit_ZeroDMA myDMA;
      Adafruit_ZeroTimer zerotimer;
      uint16_t sinewave_lookup[100];

      void FillSineWaveLookup();
      void Timer3Init();

    protected:
      void Setup() override;
      void Loop() override;

    public:
      static const int NUMBER_OF_DATA_POINTS = 100;
      FunctionGenerator();
      void Run();
      

};

#endif