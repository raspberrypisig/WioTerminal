#include "ArduinoSketchBase.h"

void ArduinoSketchBase::Run() {
    this->Setup();

    while(!done) {
        this->Loop();
    }
}


void ArduinoSketchBase::Quit() {
    done = true;
}
