#include "main.h"

#define MAX_DEPTH 2

#define GFX_WIDTH 320
#define GFX_HEIGHT 240
#define fontW 24
#define fontH 30

//COMMENT OUT IF DISPLAY IS UPSIDE DOWN
#define UPSIDEDOWN

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

const panel panels[]  = {{1,1, 19, GFX_HEIGHT / fontH}};
//const panel panels[]  = {{0,0, GFX_WIDTH / fontW, GFX_HEIGHT / fontH}};
navNode* nodes[sizeof(panels) / sizeof(panel)]; //navNodes to store navigation status
panelsList pList(panels, nodes, 1); //a list of panels and nodes
idx_t eSpiTops[MAX_DEPTH]={0};


TFT_eSPIOut eSpiOut(tft,colors,eSpiTops,pList,fontW,(fontH+1));
menuOut* constMEM outputs[] ={&eSpiOut};//list of output devices
outputsList out(outputs,1);//outputs list controller

/*
keyMap topButtons_map[]={
 {WIO_KEY_A, defaultNavCodes[enterCmd].ch, INPUT_PULLUP} ,
 {WIO_KEY_B, defaultNavCodes[downCmd].ch, INPUT_PULLUP} ,
 {WIO_KEY_C, defaultNavCodes[upCmd].ch, INPUT_PULLUP}
};
keyIn<3> topButtons(topButtons_map);
*/
//menuIn* in[]={&topButtons};

RegisterSketches *registerSketches = new RegisterSketches();

/*
void weatherstation_visual1() {
  //WeatherStation1 ws1;
  //ws1.Run();
  ArduinoSketchBase *sketch = registerSketches->Find("Visual 1");
  if (sketch != NULL) {
    sketch->Run();
  }
}
*/

result showEvent(eventMask e,navNode& nav,prompt& item) {
  char *menuTitle;
  menuTitle = (char*) item.getText();
  ArduinoSketchBase *sketch = registerSketches->Find(String(menuTitle));
  sketch->Run();
  return proceed;
}



MENU(subMenu,"Weather Station",doNothing,noEvent,noStyle
  ,OP("Visual 1",showEvent,enterEvent)
  ,OP("Visual 2",doNothing,noEvent)
  ,EXIT(BACKMENU)
);

MENU(mainMenu,"Menu",doNothing,noEvent,wrapStyle
  ,OP("Version", doNothing, noEvent)
  ,SUBMENU(subMenu)
  ,OP("Dummy", doNothing, noEvent)
  ,OP("Dummy", doNothing, noEvent)
);

NAVROOT(nav,mainMenu,MAX_DEPTH,serial,out);

navCmds nextCmd = noCmd;

void topButton1() {
  nextCmd = enterCmd;
}

void topButton2() {
  nextCmd = downCmd;
}

void topButton3() {
  nextCmd = upCmd;
}



void setup() {
  Serial.begin(115200);
   // WeatherStation();
  tft.begin();
  tft.setRotation(1);
  #ifdef UPSIDEDOWN
  tft.setRotation(3);
  #endif 
  tft.setTextSize(3);
  tft.fillScreen(TFT_BLACK);

  

  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  
  #ifdef UPSIDEDOWN
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), topButton1, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), topButton2, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), topButton3, FALLING);
  #else
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), topButton3, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), topButton2, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), topButton1, FALLING);
  #endif
}

void loop() {
  nav.poll();
  if (nextCmd != noCmd) {
    nav.doNav(nextCmd);
    nextCmd = noCmd;
  }
}