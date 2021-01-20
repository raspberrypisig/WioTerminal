#include "WeatherStation1.h"

WeatherStation1::WeatherStation1() {
  this->tft = TFT_eSPI(320,240);

  this->temperature = 22.3;
  this->humidity = 45;
  this->pressure = 1009;
}


void WeatherStation1::Run() {
  ArduinoSketchBase::Run();
}


void WeatherStation1::Setup()  {
  TFT_eSPI& tft = this->tft;
  
  tft.fillScreen(TFT_BLUE);
  
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_GREEN);
  tft.setFreeFont(FF18);
  tft.drawString("Weather Station", 160, 30);
  tft.drawLine(0, 60, 320, 60, TFT_WHITE);

  tft.setTextColor(TFT_YELLOW);
  tft.setFreeFont(FF9);
  tft.drawString("v" + String(VERSION), 160, 75);
  tft.drawLine(0, 90, 320, 90, TFT_WHITE);  

  tft.drawLine(0, 140, 320, 140, TFT_WHITE);
  tft.drawLine(0, 190, 320, 190, TFT_WHITE);
  tft.drawLine(160, 90, 160, 240, TFT_WHITE);

  tft.setTextDatum(ML_DATUM);
  tft.setTextColor(TFT_PURPLE);
  tft.setFreeFont(FF15);
  tft.drawString("TEMP.", 20, 115);

  tft.setFreeFont(FF15);
  tft.drawString("HUMID.", 20, 165);

  tft.setFreeFont(FF15);
  tft.drawString("PRESS.", 20, 215);

  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MR_DATUM);
  tft.setFreeFont(FF14);
  tft.drawString("°C", 310, 115);
  tft.drawString("%", 310, 165);
  tft.setFreeFont(FF9);
  tft.drawString("kPa", 310, 215);
  tft.setTextDatum(ML_DATUM);

  tft.setFreeFont(FF20);
}

void WeatherStation1::Loop()  {
  TFT_eSPI& tft = this->tft;

  tft.drawFloat(temperature, 1, 170, 115);
  tft.drawNumber(humidity, 170, 165);
  tft.drawNumber(pressure, 170, 215);
  delay(2000);
}

/*
void WeatherStation1::Run() {
   this->Setup();
   for (;;) {
      this->Loop();
   }   
}
*/