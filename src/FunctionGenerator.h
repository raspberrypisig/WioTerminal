#ifndef _FUNCTION_GENERATOR_H_
#define _FUNCTION_GENERATOR_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include <Adafruit_ZeroDMA.h>
#include "Adafruit_ZeroTimer.h"

#define CONFIGURE_FREQUENCY_WIDTH 30
#define CONFIGURE_FREQUENCY_SPACING 25

#define NUMBEROFPOINTS 100

enum class Waveform {SQUARE=0, SINE=1, RAMP=2, TRIANGLE=3};

enum class FunctionGeneratorProgramState {HOMESCREEN, CONFIGURE_FREQUENCY, CONFIGURE_DUTY, RUNNING, RUNFOREVER};

class FunctionGenerator : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      Adafruit_ZeroDMA myDMA;
      DmacDescriptor *descriptor;
      //Adafruit_ZeroTimer zt3 = Adafruit_ZeroTimer(3);
      Adafruit_ZeroTimer zt4 = Adafruit_ZeroTimer(4);
      uint16_t sinewave_lookup[NUMBEROFPOINTS];
      uint16_t triangle_lookup[NUMBEROFPOINTS];
      uint16_t ramp_lookup[NUMBEROFPOINTS];
      Waveform homescreen_waveform = Waveform::SQUARE;
      FunctionGeneratorProgramState state = FunctionGeneratorProgramState::HOMESCREEN;
      String waveform_names[4] = {"SQUARE", "SINE", "RAMP", "TRIANGLE"};
      uint8_t squarewave_frequency[8] = {0,0,0,0,0,0,0,0};
      uint8_t squarewave_digitoffset[8] = {9,8,7,5,4,3,1,0};
      uint8_t squarewave_currentpos = 7;
      uint8_t squarewave_dutycycle = 50;
      
      void SetupDMA();

      void FillSineWaveLookup();
      void FillTriangleLookup();
      void FillRampLookup();
      void StartSquareWaveform(long freq, uint8_t duty);
      void StartSineWaveform();
      void StartRampWaveform();
      void StartTriangleWaveform();
      void Timer3Init();
      void Timer4Init(long freq, uint8_t duty);
      void configureTimerParams();

      Waveform HomeScreen_nextWaveform();
      void HomeScreen_redraw(Waveform current, Waveform next);
      void HomeScreen_draw();
      void HomeScreen_drawSquare(bool fill);
      void HomeScreen_drawSine(bool fill);
      void HomeScreen_drawRamp(bool fill);
      void HomeScreen_drawTriangle(bool fill);
      void ConfigureFrequencyScreen();
      void FrequencyScreen_redraw();
      void ConfigureDutyScreen();
      void DutyScreen_redraw();
      void RunningScreen();

    protected:
      void Setup() override;
      void Loop() override;

    public:
      static const int NUMBER_OF_DATA_POINTS = 100;
      FunctionGenerator();
      void Run();
      

};

#endif