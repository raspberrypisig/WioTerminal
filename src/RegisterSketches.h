#include "ArduinoSketchRegistry.h"

#include "WeatherStation1.h"
#include "WeatherStation2.h"
#include "ProgramVersion.h"
#include "WifiBasic.h"
#include "WifiMyDevices.h"
#include "Buzzer.h"
#include "DigitalIO.h"
#include "DACTest.h"
#include "PWMSquare.h"






class RegisterSketches: public ArduinoSketchRegistry {
  public:
    RegisterSketches();
};