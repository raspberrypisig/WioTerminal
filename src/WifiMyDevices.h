#ifndef _WIFI_MY_DEVICES_H_
#define _WIFI_MY_DEVICES_H_

#include <Arduino.h>
#include <vector>
#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"


#include <RPCmDNS.h>

typedef struct  {
  String hostname;
  String ip;
  String service;
} mDNSDevice;



class WifiMyDevices : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      std::vector<mDNSDevice> devices;
      int deviceIndex = 0;
      unsigned int numberOfDevicesFound=0;
      void browseService(const char *service, const char *proto);
      void ShowDevice();

    protected:
      void Setup() override;
      void Loop() override;

    public:
      WifiMyDevices();
      void Run();

};

#endif