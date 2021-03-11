#include "AnalogClock.h"

AnalogClock::AnalogClock() {
    tft = TFT_eSPI(320,240);
}

void AnalogClock::Run() {
    ArduinoSketchBase::Run();
}

void alarmMatch(uint32_t flag) {
      Serial.println("Alarm Match!");
}

void AnalogClock::Setup() {
  
tft.fillScreen(TFT_DARKGREY);
  
  tft.setTextColor(TFT_WHITE, TFT_DARKGREY);  // Adding a background colour erases previous text automatically
  
  // Draw clock face
  tft.fillCircle(120, 120, 118, TFT_GREEN);
  tft.fillCircle(120, 120, 110, TFT_BLACK);

  // Draw 12 lines
  for(int i = 0; i<360; i+= 30) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*114+120;
    yy0 = sy*114+120;
    x1 = sx*100+120;
    yy1 = sy*100+120;

    tft.drawLine(x0, yy0, x1, yy1, TFT_GREEN);
  }

  // Draw 60 dots
  for(int i = 0; i<360; i+= 6) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*102+120;
    yy0 = sy*102+120;
    // Draw minute markers
    tft.drawPixel(x0, yy0, TFT_WHITE);
    
    // Draw main quadrant dots
    if(i==0 || i==180) tft.fillCircle(x0, yy0, 2, TFT_WHITE);
    if(i==90 || i==270) tft.fillCircle(x0, yy0, 2, TFT_WHITE);
  }

  tft.fillCircle(120, 121, 3, TFT_WHITE);

  // Draw text at position 120,260 using fonts 4
  // Only font numbers 2,4,6,7 are valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : . - a p m
  // Font 7 is a 7 segment font and only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : .
  //tft.drawCentreString("Time flies",120,260,4);

  connectToWiFi(analogclock_ssid, analogclock_password);
unsigned long realTime = getNTPtime();
realTime += 3 * 60 * 60;
rtc.adjust(DateTime(realTime));
now = rtc.now();
DateTime alarm = DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second() + 1);
   rtc.setAlarm(0,alarm); // match after 15 seconds
    rtc.enableAlarm(0, rtc.MATCH_HHMMSS); // match Every Day

    rtc.attachInterrupt(alarmMatch); 
//Serial.println(now.timestamp(DateTime::TIMESTAMP_FULL));
}



void AnalogClock::Loop() {
  now = rtc.now();
  hh = now.twelveHour();
  mm = now.minute();
  ss = now.second();

    // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = ss*6;                  // 0-59 -> 0-354
    mdeg = mm*6+sdeg*0.01666667;  // 0-59 -> 0-360 - includes seconds
    hdeg = hh*30+mdeg*0.0833333;  // 0-11 -> 0-360 - includes minutes and seconds
    hx = cos((hdeg-90)*0.0174532925);    
    hy = sin((hdeg-90)*0.0174532925);
    mx = cos((mdeg-90)*0.0174532925);    
    my = sin((mdeg-90)*0.0174532925);
    sx = cos((sdeg-90)*0.0174532925);    
    sy = sin((sdeg-90)*0.0174532925);

    if (ss==0 || initial) {
      initial = 0;
      // Erase hour and minute hand positions every minute
      tft.drawLine(ohx, ohy, 120, 121, TFT_BLACK);
      ohx = hx*62+121;    
      ohy = hy*62+121;
      tft.drawLine(omx, omy, 120, 121, TFT_BLACK);
      omx = mx*84+120;    
      omy = my*84+121;
    }

      // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
      tft.drawLine(osx, osy, 120, 121, TFT_BLACK);
      osx = sx*90+121;    
      osy = sy*90+121;
      tft.drawLine(osx, osy, 120, 121, TFT_RED);
      tft.drawLine(ohx, ohy, 120, 121, TFT_WHITE);
      tft.drawLine(omx, omy, 120, 121, TFT_WHITE);
      tft.drawLine(osx, osy, 120, 121, TFT_RED);

    tft.fillCircle(120, 121, 3, TFT_RED);
    //delay(5000);
}

uint8_t AnalogClock::conv2d(const char* p) {
  int8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

void AnalogClock::connectToWiFi(const char* ssid, const char* pwd) {

    Serial.println("---Connecting to WiFi network: " + String(ssid));

 



    WiFi.disconnect(true);

 

    Serial.println("Waiting for WIFI connection...");

 

    //Initiate connection

    WiFi.begin(ssid, pwd);

 

    while (WiFi.status() != WL_CONNECTED) {

        delay(500);

    }

 

    Serial.println("Connected.");

    printWifiStatus();

 

}


void AnalogClock::printWifiStatus() {

    // print the SSID of the network you're attached to:

    Serial.println("");

    Serial.print("SSID: ");

    Serial.println(WiFi.SSID());

 

    // print your WiFi shield's IP address:

    IPAddress ip = WiFi.localIP();

    Serial.print("IP Address: ");

    Serial.println(ip);

 

    // print the received signal strength:

    long rssi = WiFi.RSSI();

    Serial.print("signal strength (RSSI):");

    Serial.print(rssi);

    Serial.println(" dBm");

    Serial.println("");

}

unsigned long AnalogClock::sendNTPpacket(const char* address) {

    // set all bytes in the buffer to 0

    for (int i = 0; i < NTP_PACKET_SIZE; ++i) {

        packetBuffer[i] = 0;

    }

    // Initialize values needed to form NTP request

    // (see URL above for details on the packets)

    packetBuffer[0] = 0b11100011;   // LI, Version, Mode

    packetBuffer[1] = 0;     // Stratum, or type of clock

    packetBuffer[2] = 6;     // Polling Interval

    packetBuffer[3] = 0xEC;  // Peer Clock Precision

    // 8 bytes of zero for Root Delay & Root Dispersion

    packetBuffer[12] = 49;

    packetBuffer[13] = 0x4E;

    packetBuffer[14] = 49;

    packetBuffer[15] = 52;

 

    // all NTP fields have been given values, now

    // you can send a packet requesting a timestamp:

    udp.beginPacket(address, 123); //NTP requests are to port 123

    udp.write(packetBuffer, NTP_PACKET_SIZE);

    udp.endPacket();

}

unsigned long AnalogClock::getNTPtime() {
 
    // module returns a unsigned long time valus as secs since Jan 1, 1970 
    // unix time or 0 if a problem encounted
 
    //only send data when connected
    if (WiFi.status() == WL_CONNECTED) {
        //initializes the UDP state
        //This initializes the transfer buffer
        udp.begin(WiFi.localIP(), localPort);
 
        sendNTPpacket(analogclock_timeServer); // send an NTP packet to a time server
        // wait to see if a reply is available
        delay(1000);
        if (udp.parsePacket()) {
            Serial.println("udp packet received");
            Serial.println("");
            // We've received a packet, read the data from it
            udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
 
            //the timestamp starts at byte 40 of the received packet and is four bytes,
            // or two words, long. First, extract the two words:
 
            unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
            unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
            // combine the four bytes (two words) into a long integer
            // this is NTP time (seconds since Jan 1 1900):
            unsigned long secsSince1900 = highWord << 16 | lowWord;
            // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
            const unsigned long seventyYears = 2208988800UL;
            // subtract seventy years:
            unsigned long epoch = secsSince1900 - seventyYears;
 
            // adjust time for timezone offset in secs +/- from UTC
            // WA time offset from UTC is +8 hours (28,800 secs)
            // + East of GMT
            // - West of GMT
            long tzOffset = 28800UL;
 
            // WA local time 
            unsigned long adjustedTime;
            return adjustedTime = epoch + tzOffset;
        }
        else {
            // were not able to parse the udp packet successfully
            // clear down the udp connection
            udp.stop();
            return 0; // zero indicates a failure
        }
        // not calling ntp time frequently, stop releases resources
        udp.stop();
    }
    else {
        // network not connected
        return 0;
    }
 
}
 