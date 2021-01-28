#include "WifiMyDevices.h"

WifiMyDevices::WifiMyDevices() {
    tft = TFT_eSPI(320,240);
}

void WifiMyDevices::browseService(const char * service, const char * proto){
    Serial.printf("Browsing for service _%s._%s.local. ... ", service, proto);
    int n = MDNS.queryService(service, proto);
    if (n == 0) {
        Serial.println("no services found");
    } else {
        Serial.print(n);
        Serial.println(" service(s) found");
        for (int i = 0; i < n; ++i) {
            // Print details for each service found
            Serial.print("  ");
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(MDNS.hostname(i));
            Serial.print(" (");
            Serial.print(MDNS.IP(i));
            Serial.print(":");
            Serial.print(MDNS.port(i));
            Serial.println(")");
            mDNSDevice d;
            d.hostname = MDNS.hostname(i);
            d.ip = MDNS.IP(i).toString();
            d.service = String(service);
            devices.push_back(d);
        }
    }
    Serial.println();
}

void WifiMyDevices::Run() {
    ArduinoSketchBase::Run();
}


void WifiMyDevices::ShowDevice() {
        tft.fillScreen(TFT_RED);
        tft.setFreeFont(FF17);
        tft.setTextColor(tft.color565(224,225,232));
        tft.setCursor((320 - tft.textWidth("Devices"))/2, 25);
        tft.print("Devices");
        tft.fillRoundRect(10, 45, 300, 55, 5, tft.color565(255, 194, 179));
        tft.fillRoundRect(10, 105, 300, 55, 5, tft.color565(255, 194, 179));
        tft.fillRoundRect(10, 165, 300, 55, 5, tft.color565(255, 194, 179));
        tft.setFreeFont(FM9);
        tft.setTextColor(TFT_BLACK);
        tft.drawString("Hostname", 75, 50);
        tft.drawString("IP Address", 75, 110);
        tft.drawString("Service", 75, 170);
        tft.setFreeFont(FMB12);
        tft.setTextDatum(TL_DATUM);
        tft.setTextColor(TFT_BLACK);
        tft.drawString(devices[deviceIndex].hostname, 30, 75);
        tft.setTextColor(TFT_BLUE);
        tft.drawString(devices[deviceIndex].ip, 30, 135);
        tft.setTextColor(TFT_BLACK);
        tft.drawString(devices[deviceIndex].service, 30, 195);     
}

void WifiMyDevices::Setup() {
    Serial.begin(115200);

    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);

    if (!MDNS.begin("Mohan_WioTerminal")) {
        Serial.println("Error setting up MDNS responder!");
        while(1){
            delay(1000);
        }
    }

    tft.fillScreen(TFT_BLUE);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_GREEN);
    tft.setFreeFont(FF18);
    tft.drawString("Finding Devices...", 160, 120);

    browseService("smb", "tcp");
    browseService("ssh", "tcp");

    Serial.print("The number of devices found:");
    numberOfDevicesFound = devices.size();
    Serial.println(numberOfDevicesFound);

    if (numberOfDevicesFound > 0 ) {
        Serial.println("FOUND DEVICES.");
        ShowDevice();
    }

    /*
     browseService("http", "tcp");
     delay(1000);
     browseService("arduino", "tcp");
     delay(1000);
     browseService("workstation", "tcp");
     delay(1000);
     browseService("smb", "tcp");
     delay(1000);
     browseService("afpovertcp", "tcp");
     delay(1000);
     browseService("ftp", "tcp");
     delay(1000);
     browseService("ipp", "tcp");
     delay(1000);
     browseService("printer", "tcp");
     delay(1000);
    */

}

void WifiMyDevices::Loop() {

 if (digitalRead(WIO_5S_UP) == LOW) {
  deviceIndex = deviceIndex - 1;
  if (deviceIndex < 0) {
      deviceIndex = numberOfDevicesFound - 1; 
  }
  ShowDevice();
  Serial.println("UP");
 }

 else if (digitalRead(WIO_5S_DOWN) == LOW) {
  deviceIndex = (deviceIndex + 1) %  numberOfDevicesFound;
  Serial.println("DOWN");
  ShowDevice();
 }

  delay(500);
}