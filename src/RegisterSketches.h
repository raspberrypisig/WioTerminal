#include "ArduinoSketchRegistry.h"

#include "WeatherStation1.h"
#include "WeatherStation2.h"
#include "ProgramVersion.h"
#include "WifiBasic.h"
#include "WifiMyDevices.h"






class RegisterSketches: public ArduinoSketchRegistry {
  public:
    RegisterSketches();
};