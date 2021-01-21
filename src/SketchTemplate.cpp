#include "SketchTemplate.h"

SketchTemplate::SketchTemplate() {
    tft = TFT_eSPI(320,240);
}

void SketchTemplate::Run() {
    ArduinoSketchBase::Run();
}

void SketchTemplate::Setup() {

}

void SketchTemplate::Loop() {

}