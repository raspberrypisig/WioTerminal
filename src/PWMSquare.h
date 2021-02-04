#ifndef _PWM_SQUARE_H_
#define _PWM_SQUARE_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include <Arduino.h>
#include "Adafruit_ZeroTimer.h"

class PWMSquare : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;

    protected:
      void Setup() override;
      void Loop() override;

    public:
      PWMSquare();
      void Run();

};

#endif