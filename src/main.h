#ifndef _MAIN_H
#define _MAIN_H
//#include "weatherstation.h"
#include "WeatherStation1.h"

#include <TFT_eSPI.h>

#include <menu.h>
#include <menuIO/serialIn.h>
//#include <menuIO/altKeyIn.h>
#include <menuIO/TFT_eSPIOut.h>
#include "ArduinoSketchBase.h"
#include "RegisterSketches.h"

#define Black RGB565(0,0,0)
#define Red	RGB565(255,0,0)
#define Green RGB565(0,255,0)
#define Blue RGB565(0,0,255)
#define Gray RGB565(128,128,128)
#define LighterRed RGB565(255,150,150)
#define LighterGreen RGB565(150,255,150)
#define LighterBlue RGB565(150,150,255)
#define DarkerRed RGB565(150,0,0)
#define DarkerGreen RGB565(0,150,0)
#define DarkerBlue RGB565(0,0,150)
#define Cyan RGB565(0,255,255)
#define Magenta RGB565(255,0,255)
#define Yellow RGB565(255,255,0)
#define White RGB565(255,255,255)

#define BTN_SEL WIO_5S_PRESS  // Select button
#define BTN_UP WIO_5S_UP // Up
#define BTN_DOWN WIO_5S_DOWN // Down
#define BTN_LEFT WIO_5S_LEFT // Left
#define BTN_RIGHT WIO_5S_RIGHT // Right

#define BACKMENU "<---Back--------"
#define NEXTMENU "--Next--------->"

#endif