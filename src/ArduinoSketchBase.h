#ifndef _ARDUINO_SKETCH_BASE
#define _ARDUINO_SKETCH_BASE

class ArduinoSketchBase {
  protected:
    virtual void Setup() = 0;
    virtual void Loop() = 0;
  public:
    void Run();  
};

#endif