#ifndef _ARDUINO_SKETCH_BASE
#define _ARDUINO_SKETCH_BASE

class ArduinoSketchBase {
  protected:
    void Run();
    virtual void Setup() = 0;
    virtual void Loop() = 0;
};

#endif