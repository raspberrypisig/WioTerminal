#include "ArduinoSketchRegistry.h"


//ArduinoSketchRegistry::ArduinoSketchRegistry() { 
//}

void ArduinoSketchRegistry::Register(String menuName, ArduinoSketchBase* sketch) {
  arduinoSketchMap.insert(std::make_pair(menuName, sketch));
}

ArduinoSketchBase* ArduinoSketchRegistry::Find(String menuName) {
    if(arduinoSketchMap.find(menuName)!=arduinoSketchMap.end())
    {
        return  arduinoSketchMap[menuName];
    }

    return NULL;
}