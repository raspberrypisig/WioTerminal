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
        }
    }
    Serial.println();
}

void WifiMyDevices::Run() {
    ArduinoSketchBase::Run();
}

void WifiMyDevices::Setup() {
    Serial.begin(115200);

    if (!MDNS.begin("Mohan_WioTerminal")) {
        Serial.println("Error setting up MDNS responder!");
        while(1){
            delay(1000);
        }
    }

    browseService("smb", "tcp");
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

}