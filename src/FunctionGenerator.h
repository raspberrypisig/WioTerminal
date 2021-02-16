#ifndef _FUNCTION_GENERATOR_H_
#define _FUNCTION_GENERATOR_H_

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#include "ArduinoSketchBase.h"

#include <Adafruit_ZeroDMA.h>
#include "Adafruit_ZeroTimer.h"

enum class Waveform {SQUARE=0, SINE=1, RAMP=2, TRIANGLE=3};

enum class FunctionGeneratorProgramState {HOMESCREEN, CONFIGURE_FREQUENCY, CONFIGURE_DUTY, RUNNING};

class FunctionGenerator : public ArduinoSketchBase {
    private: 
      TFT_eSPI tft;
      Adafruit_ZeroDMA myDMA;
      Adafruit_ZeroTimer  zerotimer = Adafruit_ZeroTimer(3);
      uint16_t sinewave_lookup[100];
      Waveform homescreen_waveform = Waveform::SQUARE;
      FunctionGeneratorProgramState state = FunctionGeneratorProgramState::HOMESCREEN;
      String waveform_names[4] = {"SQUARE", "SINE", "RAMP", "TRIANGLE"};

      
      void FillSineWaveLookup();
      void Timer3Init();

      Waveform HomeScreen_nextWaveform();
      void HomeScreen_redraw(Waveform current, Waveform next);
      void HomeScreen_drawSquare(bool fill);
      void HomeScreen_drawSine(bool fill);
      void HomeScreen_drawRamp(bool fill);
      void HomeScreen_drawTriangle(bool fill);
      void ConfigureFrequencyScreen();
      void ConfigureDutyScreen();
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