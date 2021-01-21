#ifndef _MOHAN_VERSION_H_
#define _MOHAN_VERSION_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include "Version.h"

class ProgramVersion : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;

    protected:
      void Setup() override;
      void Loop() override;

    public:
      ProgramVersion();
      void Run();

};

#endif