#include "ArduinoSketchRegistry.h"

#include "WeatherStation1.h"
#include "WeatherStation2.h"
#include "ProgramVersion.h"
#include "WifiBasic.h"






class RegisterSketches: public ArduinoSketchRegistry {
  public:
    RegisterSketches();
};