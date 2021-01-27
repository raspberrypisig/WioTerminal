#include "WifiBasic.h"

WifiBasic::WifiBasic() {
    tft = TFT_eSPI(320,240);
}

void WifiBasic::Run() {
    ArduinoSketchBase::Run();
}

void WifiBasic::displayMacAddress(byte* mac) {
  tft.print(mac[0], HEX);
  tft.print(":");
  tft.print(mac[1], HEX);
  tft.print(":");
  tft.print(mac[2], HEX);
  tft.print(":");
  tft.print(mac[3], HEX);
  tft.print(":");
  tft.print(mac[4], HEX);
  tft.print(":");
  tft.print(mac[5], HEX);  
}

void WifiBasic::Setup() {
    //Serial.begin(115200);
    //wifiMulti.addAP("MelbPC-NUE-5", "peachspeak38");
    wifiMulti.addAP("MelbPC-NUE", "peachspeak38");
    //wifiMulti.addAP("mycrib5g", "peachspeak38");   
    wifiMulti.addAP("mycrib", "peachspeak38");

    Serial.println("Connecting Wifi...");
    byte mac[8];

    tft.fillScreen(TFT_BLUE);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(FF18);
    tft.drawString("Connecting Wifi...", 160, 120);

    if (wifiMulti.run() == WL_CONNECTED) {
        WiFi.macAddress(mac);
        /*
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("SSID:");
        Serial.println(WiFi.SSID());
        Serial.println("MAC:");
        Serial.print(mac[0],HEX);
        Serial.print(":");
        Serial.print(mac[1],HEX);
        Serial.print(":");
        Serial.print(mac[2],HEX);
        Serial.print(":");
        Serial.print(mac[3],HEX);
        Serial.print(":");
        Serial.print(mac[4],HEX);
        Serial.print(":");
        Serial.println(mac[5],HEX);        
        Serial.println();        
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        */

        tft.fillScreen(TFT_RED);
        tft.setFreeFont(FF17);
        tft.setTextColor(tft.color565(224,225,232));
        tft.setCursor((320 - tft.textWidth("WIFI"))/2, 25);
        tft.print("WIFI");
        tft.fillRoundRect(10, 45, 300, 55, 5, tft.color565(255, 194, 179));
        tft.fillRoundRect(10, 105, 300, 55, 5, tft.color565(255, 194, 179));
        tft.fillRoundRect(10, 165, 300, 55, 5, tft.color565(255, 194, 179));
        tft.setFreeFont(FM9);
        tft.setTextColor(TFT_BLACK);
        tft.drawString("SSID", 75, 50);
        tft.drawString("MAC", 75, 110);
        tft.drawString("IP Address", 75, 170);
        tft.setFreeFont(FMB12);
        tft.setTextColor(TFT_BLACK);
        tft.drawString(WiFi.SSID(), 110, 75);
        //tft.setTextColor(tft.color565(224,225,232));
        tft.setCursor(35, 140);
        displayMacAddress(mac);
        //tft.drawNumber(100, 110, 135);
        tft.setTextColor(TFT_BLUE);
        tft.drawString(WiFi.localIP().toString(), 130, 195);        
    }
}

void WifiBasic::Loop() {

}