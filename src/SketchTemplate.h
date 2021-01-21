#ifndef _SKETCH_TEMPLATE_H_
#define _SKETCH_TEMPLATE_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

class SketchTemplate : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;

    protected:
      void Setup() override;
      void Loop() override;

    public:
      SketchTemplate();
      void Run();

};

#endif