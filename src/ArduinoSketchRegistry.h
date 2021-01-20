#ifndef _ARDUINO_SKETCH_REGISTRY
#define _ARDUINO_SKETCH_REGISTRY

#include "ArduinoSketchBase.h"
#include "Arduino.h"
#undef min
#undef max
#include <map>
#include <utility>

template<typename T> ArduinoSketchBase* createArduinoSketch() {
    return new T;
}

typedef std::map<String, ArduinoSketchBase*(*)()> ArduinoSketchMap;


class ArduinoSketchRegistry {
  private:
    std::map<String, ArduinoSketchBase*> arduinoSketchMap;
  public:
    //ArduinoSketchRegistry();
    void Register(String menuName, ArduinoSketchBase* sketch);
    ArduinoSketchBase* Find(String menuName);
};

#endif