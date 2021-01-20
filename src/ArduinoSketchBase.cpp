#include "ArduinoSketchBase.h"

void ArduinoSketchBase::Run() {
    this->Setup();

    for(;;) {
        this->Loop();
    }
}

