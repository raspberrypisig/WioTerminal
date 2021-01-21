#include "ProgramVersion.h"

ProgramVersion::ProgramVersion() {
  tft = TFT_eSPI(320,240);
}

void ProgramVersion::Run() {
    ArduinoSketchBase::Run();
}

void ProgramVersion::Setup() {
  tft.fillScreen(TFT_BLUE);
  
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_GREEN);
  tft.setFreeFont(FF18);
  tft.drawString("Version: " + String(VERSION), 160, 120);
}

void ProgramVersion::Loop() {

}