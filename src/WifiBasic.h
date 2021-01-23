#ifndef _SKETCH_TEMPLATE_H_
#define _SKETCH_TEMPLATE_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include "rpcWiFi.h"
#include <WiFiMulti.h>

class WifiBasic : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      WiFiMulti wifiMulti;
      void displayMacAddress(byte* mac);

    protected:
      void Setup() override;
      void Loop() override;

    public:
      WifiBasic();
      void Run();

};

#endif