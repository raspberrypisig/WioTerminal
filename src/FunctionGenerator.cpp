#include "FunctionGenerator.h"



FunctionGenerator::FunctionGenerator() {
    tft = TFT_eSPI(320,240);

    
}

void FunctionGenerator::Run() {
    ArduinoSketchBase::Run();
}

void FunctionGenerator::Setup() {
    Serial.begin(115200);

    tft.fillScreen(TFT_BLUE);

    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_RED);
    tft.setFreeFont(FF18);
    tft.drawString("FunctionGen", 160, 20);

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

}

void FunctionGenerator::FillSineWaveLookup() {
  float phase = TWO_PI/NUMBER_OF_DATA_POINTS;

  for (int i=0; i<NUMBER_OF_DATA_POINTS; i++) {
     sinewave_lookup[i] =  4000 * sin(phase * i) + 4096/2;
  }
}


void FunctionGenerator::Timer3Init() {
    zerotimer = Adafruit_ZeroTimer(3);

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
    zerotimer.setCallback(false, TC_CALLBACK_CC_CHANNEL0, NULL);
    zerotimer.enable(true);

}