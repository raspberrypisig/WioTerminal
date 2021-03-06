#include "RegisterSketches.h"

RegisterSketches::RegisterSketches() {

   Register("Visual 1",           new WeatherStation1());
   Register("Visual 2",           new WeatherStation2());
   Register("Version",            new ProgramVersion());
   Register("Wifi Basic",         new WifiBasic());
   Register("My Devices",         new WifiMyDevices());
   Register("Buzzer",             new Buzzer());
   Register("DigitalIO",          new DigitalIO());
   Register("DACTest",            new DACTest());
   Register("PWMSquare",          new PWMSquare());
   Register("FunctionGen",        new FunctionGenerator() );
   Register("AnalogClock",        new AnalogClock());
}
