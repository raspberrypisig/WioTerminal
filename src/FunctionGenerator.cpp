#include "FunctionGenerator.h"



FunctionGenerator::FunctionGenerator() {
    tft = TFT_eSPI(320,240);
    
}

void FunctionGenerator::Run() {
    ArduinoSketchBase::Run();
}

void FunctionGenerator::Setup() {
  Serial.begin(115200);

  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);

  HomeScreen_draw();

	analogWriteResolution(12);
	analogWrite(DAC0,0);   // DAC init setup DAC pin and zero it

    FillSineWaveLookup();
    
    //while (DAC->SYNCBUSY.bit.DATA0);
    //DAC->DATA[0].reg = 123;

    /*

    myDMA.setTrigger(TC3_DMAC_ID_OVF);
    myDMA.setAction(DMA_TRIGGER_ACTON_BEAT);
    myDMA.allocate();

    myDMA.addDescriptor(
    sinewave_lookup,                    // move data from here
    (void *)(&DAC->DATA[0].reg), // to here (M4)

    NUMBER_OF_DATA_POINTS,                      // this many...
    DMA_BEAT_SIZE_HWORD,               // bytes/hword/words
    true,                             // increment source addr?
    false);                           // increment dest addr?

    myDMA.startJob();
   
    */
  
}

void FunctionGenerator::Loop() {
  if (state == FunctionGeneratorProgramState::HOMESCREEN && digitalRead(WIO_5S_RIGHT) == LOW) {
    Waveform next_waveform = HomeScreen_nextWaveform();
    HomeScreen_redraw(homescreen_waveform, next_waveform);
    homescreen_waveform = next_waveform;
  }

  else if (state == FunctionGeneratorProgramState::HOMESCREEN &&  digitalRead(WIO_5S_PRESS) == LOW) {
    if (homescreen_waveform == Waveform::SQUARE) {
      state = FunctionGeneratorProgramState::CONFIGURE_FREQUENCY;
      ConfigureFrequencyScreen();
    }
    else {
      state = FunctionGeneratorProgramState::RUNNING;
      RunningScreen();
    }  
  }

  else if (state == FunctionGeneratorProgramState::CONFIGURE_FREQUENCY &&  digitalRead(WIO_5S_PRESS) == LOW) {
    state = FunctionGeneratorProgramState::CONFIGURE_DUTY;
    ConfigureDutyScreen();
  }

  else if (state == FunctionGeneratorProgramState::CONFIGURE_FREQUENCY &&  digitalRead(WIO_5S_UP) == LOW) {
    
  } 

  else if (state == FunctionGeneratorProgramState::CONFIGURE_FREQUENCY &&  digitalRead(WIO_5S_DOWN) == LOW) {
    
  }  

  else if (state == FunctionGeneratorProgramState::CONFIGURE_FREQUENCY &&  digitalRead(WIO_5S_LEFT) == LOW) {
    if (squarewave_currentpos < 7) {
      squarewave_currentpos++;
      FrequencyScreen_redraw();
    }    
  } 

  else if (state == FunctionGeneratorProgramState::CONFIGURE_FREQUENCY &&  digitalRead(WIO_5S_RIGHT) == LOW) {

    if (squarewave_currentpos >= 1) {
      squarewave_currentpos--;
      FrequencyScreen_redraw();
    }
    Serial.print("pos:");
    Serial.println(squarewave_currentpos);

  } 

  else if (state == FunctionGeneratorProgramState::CONFIGURE_DUTY &&  digitalRead(WIO_5S_PRESS) == LOW) {
    state = FunctionGeneratorProgramState::RUNNING;
    RunningScreen();
  }

  else if (state == FunctionGeneratorProgramState::RUNNING &&  digitalRead(WIO_5S_PRESS) == LOW) {
    state = FunctionGeneratorProgramState::HOMESCREEN;
    HomeScreen_draw();
  }

  delay(100);
}

void FunctionGenerator::FillSineWaveLookup() {
  float phase = TWO_PI/NUMBER_OF_DATA_POINTS;

  for (int i=0; i<NUMBER_OF_DATA_POINTS; i++) {
     sinewave_lookup[i] =  4000 * sin(phase * i) + 4096/2;
  }
}


void FunctionGenerator::Timer3Init() {
   

/*
  uint16_t divider  = 1;
  uint16_t compare = 0;
  tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;

  if ((freq < 24000000) && (freq > 800)) {
    divider = 1;
    prescaler = TC_CLOCK_PRESCALER_DIV1;
    compare = 48000000/freq;
  } else if (freq > 400) {
    divider = 2;
    prescaler = TC_CLOCK_PRESCALER_DIV2;
    compare = (48000000/2)/freq;
  } else if (freq > 200) {
    divider = 4;
    prescaler = TC_CLOCK_PRESCALER_DIV4;
    compare = (48000000/4)/freq;
  } else if (freq > 100) {
    divider = 8;
    prescaler = TC_CLOCK_PRESCALER_DIV8;
    compare = (48000000/8)/freq;
  } else if (freq > 50) {
    divider = 16;
    prescaler = TC_CLOCK_PRESCALER_DIV16;
    compare = (48000000/16)/freq;
  } else if (freq > 12) {
    divider = 64;
    prescaler = TC_CLOCK_PRESCALER_DIV64;
    compare = (48000000/64)/freq;
  } else if (freq > 3) {
    divider = 256;
    prescaler = TC_CLOCK_PRESCALER_DIV256;
    compare = (48000000/256)/freq;
  } else if (freq >= 0.75) {
    divider = 1024;
    prescaler = TC_CLOCK_PRESCALER_DIV1024;
    compare = (48000000/1024)/freq;
  } else {
    Serial.println("Invalid frequency");
    while (1) delay(10);
  }
  Serial.print("Divider:"); Serial.println(divider);
  Serial.print("Compare:"); Serial.println(compare);
  Serial.print("Final freq:"); Serial.println((int)(48000000/compare));
*/
    float freq = 1000.f * NUMBER_OF_DATA_POINTS;
    tc_clock_prescaler  prescaler = TC_CLOCK_PRESCALER_DIV1;
    uint16_t compare = 48000000/freq;

    zerotimer.enable(false);
    zerotimer.configure(prescaler,       // prescaler
          TC_COUNTER_SIZE_16BIT,       // bit width of timer/counter
          TC_WAVE_GENERATION_MATCH_PWM // frequency or PWM mode
          );

    zerotimer.setCompare(0, compare);
    //zerotimer.setCallback(false, TC_CALLBACK_CC_CHANNEL0, NULL);
    zerotimer.enable(true);

}

Waveform FunctionGenerator::HomeScreen_nextWaveform() {
  switch(homescreen_waveform) {
    case Waveform::SQUARE:
      return Waveform::SINE;
      break;
    case Waveform::SINE:
      return Waveform::RAMP;
      break;
    case Waveform::RAMP:
      return Waveform::TRIANGLE;
      break;
    case Waveform::TRIANGLE:
      return Waveform::SQUARE;
      break;                
  }

  return Waveform::SQUARE;
}

void FunctionGenerator::HomeScreen_redraw(Waveform current, Waveform next) {
    switch(current) {
      case Waveform::SQUARE:
        HomeScreen_drawSquare(false);
      break;

      case Waveform::SINE:
        HomeScreen_drawSine(false);
      break;

      case Waveform::RAMP:
        HomeScreen_drawRamp(false);
      break;

      case Waveform::TRIANGLE:
        HomeScreen_drawTriangle(false);
      break;            

    }

    switch(next) {
      case Waveform::SQUARE:
        HomeScreen_drawSquare(true);
      break;

      case Waveform::SINE:
        HomeScreen_drawSine(true);
      break;

      case Waveform::RAMP:
        HomeScreen_drawRamp(true);
      break;

      case Waveform::TRIANGLE:
        HomeScreen_drawTriangle(true);
      break;          
    }
}

void FunctionGenerator::HomeScreen_drawSquare(bool fill) {
 tft.setTextDatum(TL_DATUM);


  if (fill) {
    tft.fillRoundRect(30,80, 120,60,5, TFT_GREEN);
     tft.setTextColor(TFT_PURPLE);
  }

  else {
    tft.fillRoundRect(30,80,120,60,5, TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
  }
  tft.setTextDatum(MC_DATUM);

  tft.drawString("SQUARE", 90, 110);
}

void FunctionGenerator::HomeScreen_drawSine(bool fill) {
 tft.setTextDatum(TL_DATUM);


  if (fill) {
    tft.fillRoundRect(170,80, 120,60,5, TFT_GREEN);
     tft.setTextColor(TFT_PURPLE);
  }

  else {
    tft.fillRoundRect(170,80,120,60,5, TFT_BLACK);
     tft.setTextColor(TFT_WHITE);
  }
  tft.setTextDatum(MC_DATUM);

  tft.drawString("SINE", 230, 110);
}

void FunctionGenerator::HomeScreen_drawRamp(bool fill) {
 tft.setTextDatum(TL_DATUM);

  if (fill) {
    tft.fillRoundRect(30,160, 120,60,5, TFT_GREEN);
    tft.setTextColor(TFT_PURPLE);
  }

  else {
    tft.fillRoundRect(30,160,120,60,5, TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
  }
  tft.setTextDatum(MC_DATUM);

  tft.drawString("RAMP", 90, 190);
}

void FunctionGenerator::HomeScreen_drawTriangle(bool fill) {
 tft.setTextDatum(TL_DATUM);


  if (fill) {
    tft.fillRoundRect(170,160, 120,60,5, TFT_GREEN);
    tft.setTextColor(TFT_PURPLE);
  }

  else {
    tft.fillRoundRect(170,160,120,60,5, TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
  }
  tft.setTextDatum(MC_DATUM);

  tft.drawString("TRI", 230, 190);
}

void FunctionGenerator::ConfigureFrequencyScreen() {

        tft.setTextDatum(MC_DATUM);
        tft.fillScreen(TFT_RED);
        tft.setFreeFont(FF17);
        tft.setTextColor(tft.color565(224,225,232));
        tft.drawString("Function Generator", 160, 20);
        tft.setTextColor(TFT_WHITE);
        tft.drawString("SET FREQUENCY(Hz)", 160, 60);

        tft.setFreeFont(FF44);
        
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 1*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 3*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 4*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 5*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 7*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 8*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 9*CONFIGURE_FREQUENCY_WIDTH,130);
        
        tft.setFreeFont(FF17);        
        tft.drawRect(10, 100, 32,60,TFT_YELLOW );
}

void FunctionGenerator::ConfigureDutyScreen() {
        tft.setTextDatum(MC_DATUM);
        tft.fillScreen(TFT_RED);
        tft.setFreeFont(FF17);
        tft.setTextColor(tft.color565(224,225,232));
        tft.drawString("Function Generator", 160, 20);
        tft.drawString("SET DUTY CYCLE(%)", 160, 60);
} 

void FunctionGenerator::RunningScreen() {
        tft.setTextDatum(MC_DATUM);
        tft.fillScreen(TFT_RED);
        tft.setFreeFont(FF17);
        tft.setTextColor(tft.color565(224,225,232));
        tft.drawString("Function Generator", 160, 20);
        tft.fillRoundRect(10, 45, 300, 55, 5, tft.color565(255, 194, 179));
        tft.fillRoundRect(10, 105, 300, 55, 5, tft.color565(255, 194, 179));
        if (homescreen_waveform == Waveform::SQUARE) {
          tft.fillRoundRect(10, 165, 300, 55, 5, tft.color565(255, 194, 179));
        }
        
        
        tft.setFreeFont(FM9);
        tft.setTextColor(TFT_BLACK);
        tft.drawString("Waveform", 160, 50);
        tft.drawString("Frequency(Hz)", 160, 110);
        if (homescreen_waveform == Waveform::SQUARE) {
        tft.drawString("Duty Cycle(%)", 160, 170);
        }


        tft.setFreeFont(FMB12);
        tft.setTextColor(TFT_BLACK);
        tft.drawString(waveform_names[(int)homescreen_waveform], 160, 72);
        //tft.setTextColor(tft.color565(224,225,232));
        tft.setCursor(35, 140);
        //displayMacAddress(mac);
        tft.drawNumber(1000, 160, 132);
        if (homescreen_waveform == Waveform::SQUARE) {
        tft.setTextColor(TFT_BLUE);
        tft.drawString("moo", 160, 192); 
        }
}

void FunctionGenerator::HomeScreen_draw() {
  tft.fillScreen(TFT_BLUE);

  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_RED);
  tft.setFreeFont(FF18);
  tft.drawString("FunctionGen", 160, 20);
  tft.setTextDatum(TL_DATUM);

  HomeScreen_drawSquare(true);
  HomeScreen_drawSine(false);
  HomeScreen_drawRamp(false);
  HomeScreen_drawTriangle(false);
}

void FunctionGenerator::FrequencyScreen_redraw() {
        tft.setFreeFont(FF44);
        
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 1*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 3*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 4*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 5*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 7*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 8*CONFIGURE_FREQUENCY_WIDTH,130);
        tft.drawNumber(0,CONFIGURE_FREQUENCY_SPACING + 9*CONFIGURE_FREQUENCY_WIDTH,130);
        
        tft.setFreeFont(FF17);  
        for (int i=0; i<=9; i++) {
          tft.drawRect(10+CONFIGURE_FREQUENCY_WIDTH * i, 100, 32,60,TFT_RED );
        }      

        Serial.print("left:");
        Serial.println(10+CONFIGURE_FREQUENCY_WIDTH*squarewave_digitoffset[squarewave_currentpos]);
        tft.drawRect(10+CONFIGURE_FREQUENCY_WIDTH*squarewave_digitoffset[squarewave_currentpos], 100, 32,60,TFT_YELLOW );
}

void FunctionGenerator::DutyScreen_redraw() {
  
}