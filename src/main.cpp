#include "main.h"

#define MAX_DEPTH 2

#define GFX_WIDTH 320
#define GFX_HEIGHT 240
//#define fontW 8
//#define fontH 10
//#define fontW 16
//#define fontH 20
#define fontW 24
#define fontH 30


using namespace Menu;

TFT_eSPI tft = TFT_eSPI();

result doAlert(eventMask e, prompt &item);

serialIn serial(Serial);

const colorDef<uint16_t> colors[6] MEMMODE={
  {{(uint16_t)Black,(uint16_t)Black}, {(uint16_t)Black, (uint16_t)LighterBlue,  (uint16_t)Blue}},//bgColor
  {{(uint16_t)Gray, (uint16_t)Gray},  {(uint16_t)White, (uint16_t)White, (uint16_t)White}},//fgColor
  {{(uint16_t)White,(uint16_t)Black}, {(uint16_t)Yellow,(uint16_t)Yellow,(uint16_t)Red}},//valColor
  {{(uint16_t)White,(uint16_t)Black}, {(uint16_t)White, (uint16_t)Yellow,(uint16_t)Yellow}},//unitColor
  {{(uint16_t)White,(uint16_t)Gray},  {(uint16_t)Black, (uint16_t)Blue,  (uint16_t)White}},//cursorColor
  {{(uint16_t)White,(uint16_t)Yellow},{(uint16_t)Black,  (uint16_t)Red,   (uint16_t)Red}},//titleColor
};

/*
const colorDef<uint16_t> colors[6] ={
  {{(uint16_t)Black,(uint16_t)Black}, {(uint16_t)Black, (uint16_t)Blue,  (uint16_t)Blue}},//bgColor
  {{(uint16_t)Gray, (uint16_t)Gray},  {(uint16_t)White, (uint16_t)White, (uint16_t)White}},//fgColor
  {{(uint16_t)White,(uint16_t)Black}, {(uint16_t)Yellow,(uint16_t)Yellow,(uint16_t)Red}},//valColor
  {{(uint16_t)White,(uint16_t)Black}, {(uint16_t)White, (uint16_t)Yellow,(uint16_t)Yellow}},//unitColor
  {{(uint16_t)White,(uint16_t)Gray},  {(uint16_t)Black, (uint16_t)Blue,  (uint16_t)White}},//cursorColor
  {{(uint16_t)White,(uint16_t)Yellow},{(uint16_t)Blue,  (uint16_t)Red,   (uint16_t)Red}},//titleColor
};
*/

const panel panels[]  = {{1,1, 19, GFX_HEIGHT / fontH}};
//const panel panels[]  = {{0,0, GFX_WIDTH / fontW, GFX_HEIGHT / fontH}};
navNode* nodes[sizeof(panels) / sizeof(panel)]; //navNodes to store navigation status
panelsList pList(panels, nodes, 1); //a list of panels and nodes
idx_t eSpiTops[MAX_DEPTH]={0};


TFT_eSPIOut eSpiOut(tft,colors,eSpiTops,pList,fontW,(fontH+1));
menuOut* constMEM outputs[] ={&eSpiOut};//list of output devices
outputsList out(outputs,1);//outputs list controller

MENU(subMenu,"Weather Station",doNothing,noEvent,noStyle
  ,OP("Weather Station 1",doNothing,noEvent)
  ,OP("Weather Station 2",doNothing,noEvent)
  ,EXIT("<Back")
);

MENU(mainMenu,"Menu",doNothing,noEvent,wrapStyle
  ,OP("Version", doNothing, noEvent)
  ,SUBMENU(subMenu)
  ,EXIT("<Back")
);

NAVROOT(nav,mainMenu,MAX_DEPTH,serial,out);

void setup() {
  Serial.begin(115200);
  delay(5000);
  for (int i=0; i<100; i++) {
    Serial.println(i);
  }
   // WeatherStation();
  tft.begin();
  tft.setRotation(3);
  //tft.setTextSize(2);
  tft.setTextSize(3);
  tft.fillScreen(TFT_BLACK);
  
  //tft.setTextDatum(MC_DATUM);
  //tft.setTextColor(TFT_GREEN);
  //tft.setFreeFont(FF18);
}

void loop() {
  nav.poll();
}