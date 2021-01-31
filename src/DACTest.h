#ifndef _DACTest_H_
#define _DACTest_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

class DACTest : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;

    protected:
      void Setup() override;
      void Loop() override;

    public:
      DACTest();
      void Run();

};

#endif