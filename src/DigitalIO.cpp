#include "DigitalIO.h"

DigitalIO::DigitalIO() {
    tft = TFT_eSPI(320,240);
}

void DigitalIO::Run() {
    ArduinoSketchBase::Run();
}

void DigitalIO::Setup() {
  TFT_eSPI& tft = this->tft;
  
  tft.fillScreen(TFT_BLUE);
  
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_GREEN);
  tft.setFreeFont(FF18);
  tft.drawString("HIGH on D0(pin13)", 160, 120);

  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);

}

void DigitalIO::Loop() {

}