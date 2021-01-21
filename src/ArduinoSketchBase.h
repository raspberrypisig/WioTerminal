#ifndef _ARDUINO_SKETCH_BASE
#define _ARDUINO_SKETCH_BASE

class ArduinoSketchBase {
  private:
    bool done = false;
  protected:
    virtual void Setup() = 0;
    virtual void Loop() = 0;
  public:
    void Run(); 
    void Quit(); 
};

#endif