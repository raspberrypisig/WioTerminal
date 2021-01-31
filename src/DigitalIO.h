#ifndef _DigitalIO_H_
#define _DigitalIO_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

class DigitalIO : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;

    protected:
      void Setup() override;
      void Loop() override;

    public:
      DigitalIO();
      void Run();

};

#endif