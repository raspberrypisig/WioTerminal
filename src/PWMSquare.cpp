#include "PWMSquare.h"

// timer tester
Adafruit_ZeroTimer zt3 = Adafruit_ZeroTimer(3);
Adafruit_ZeroTimer zt4 = Adafruit_ZeroTimer(4);
Adafruit_ZeroTimer zt5 = Adafruit_ZeroTimer(5);

/* Valid PWM outs:

FOR SAMD21:
  Timer3: channel 0 on D2 or D10, channel 1 on D5 or D12
  Timer4: channel 0 on SDA or A1, channel 2 on SCL or A2
  Timer5: channel 0 on MOSI, channel 1 on SCK

FOR SAMD51:
  Timer3: channel 0 on D10 or MISO, channel 1 on D11
  Timer4: channel 0 on A4, D7, or D1, channel 2 on A5, D4, or D0
  Timer5: channel 0 on D5, channel 1 on D6
*/

#if defined(__SAMD51__)
#define TIMER3_OUT0 10
#define TIMER3_OUT1 11

#define TIMER4_OUT0 A4
#define TIMER4_OUT1 A5

#define TIMER5_OUT1 6
#else
#define TIMER3_OUT0 10
#define TIMER3_OUT1 12

#define TIMER4_OUT0 A1
#define TIMER4_OUT1 A2

#define TIMER5_OUT1 SCK
#endif

PWMSquare::PWMSquare() {
    tft = TFT_eSPI(320,240);
}

void PWMSquare::Run() {
    ArduinoSketchBase::Run();
}


/* 
Trying to get a 10KHz square wave 

I believe f_GCLK_TC is 48Mhz. Single-slope PWM.

f_required = f_GCLK_TC/(N(TOP + 1))

N=prescaler
TOP=max number timer counts to

CC[0] is TOP, CC[1] is duty cycle(50% duty cycle, CC[1] = CC[0]/2) 

TOP = ( f_GCLK_TC/(N * f_required) ) - 1

*/

void PWMSquare::Setup() {
  /********************* Timer #3, 16 bit, two PWM outs, period = 65535 */
  zt3.configure(TC_CLOCK_PRESCALER_DIV2, // prescaler
                TC_COUNTER_SIZE_16BIT,   // bit width of timer/counter
                TC_WAVE_GENERATION_NORMAL_PWM // frequency or PWM mode
                );
  uint16_t desired_frequency = 10000;

  //48000000 48MHz clock freq of timer
  // 2 is prescaler
  uint32_t top = ( uint32_t) (48000000/(2 * desired_frequency) -1);
  
  zt3.setCompare(0, top);
  zt3.setCompare(1, top/2);
  zt3.enable(true);
  /********************* Timer #4, 8 bit, two PWM outs, period = 100 */
  /*
  zt4.configure(TC_CLOCK_PRESCALER_DIV1, // prescaler
                TC_COUNTER_SIZE_8BIT,   // bit width of timer/counter
                TC_WAVE_GENERATION_NORMAL_PWM // frequency or PWM mode
                );
  zt4.setPeriodMatch(100, 20, 0);      // channel 0, 20/100 count
  zt4.setPeriodMatch(100, 75, 1);      // channel 1, 75/100 count
  if (! zt4.PWMout(true, 1, TIMER4_OUT1)) {
    Serial.println("Failed to configure PWM output");
  }
  if (! zt4.PWMout(true, 0, TIMER4_OUT0)) {
    Serial.println("Failed to configure PWM output");
  }
  zt4.enable(true);
  */
  /********************* Timer #5, 16 bit, one PWM out, period = 1000 */
  /*
  zt5.configure(TC_CLOCK_PRESCALER_DIV1, // prescaler
                TC_COUNTER_SIZE_16BIT,   // bit width of timer/counter
                TC_WAVE_GENERATION_MATCH_PWM // frequency or PWM mode
                );
  zt5.setPeriodMatch(1000, 200);      // channel 1 only, 200/1000 count
  if (! zt5.PWMout(true, 1, TIMER5_OUT1)) {
    Serial.println("Failed to configure PWM output");
  }
  zt5.enable(true);
  */
  /*********************/    



}

void PWMSquare::Loop() {

}