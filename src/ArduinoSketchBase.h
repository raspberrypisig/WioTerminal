class ArduinoSketchBase {
  protected:
    void Run();
    virtual void Setup() = 0;
    virtual void Loop() = 0;
};