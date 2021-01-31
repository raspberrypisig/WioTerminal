#include "DACTest.h"

DACTest::DACTest() {
    tft = TFT_eSPI(320,240);
}

void DACTest::Run() {
    ArduinoSketchBase::Run();
}

void DACTest::Setup() {

  TFT_eSPI& tft = this->tft;
  
  tft.fillScreen(TFT_BLUE);
  
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_GREEN);
  tft.setFreeFont(FF18);
  tft.drawString("DAC0: value 2047", 160, 120);
  

  pinMode(DAC0, OUTPUT);
  analogWriteResolution(12);
  analogWrite(DAC0, 2047);
}

void DACTest::Loop() {

}