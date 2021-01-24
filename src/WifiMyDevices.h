#ifndef _WIFI_MY_DEVICES_H_
#define _WIFI_MY_DEVICES_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include <RPCmDNS.h>

class WifiMyDevices : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      void browseService(const char *service, const char *proto);

    protected:
      void Setup() override;
      void Loop() override;

    public:
      WifiMyDevices();
      void Run();

};

#endif