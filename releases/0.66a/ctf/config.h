/**
   DIY RF Laptimer by Andrey Voroshkov (bshep)
   SPI driver based on fs_skyrf_58g-main.c by Simon Chambers
   fast ADC reading code is by "jmknapp" from Arduino forum
   fast port I/O code from http://masteringarduino.blogspot.com.by/2013/10/fastest-and-smallest-digitalread-and.html
   CTF code by Carlos Costa (SeekNDFPV @ youtube)

  The MIT License (MIT)

  Copyright (c) 2016 by Andrey Voroshkov (bshep)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

int lcd_key     = 0;
int adc_key_in  = 0;
//int brightnessSetting = 0;

String pickcolour = String(""); // r/l

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

uint16_t readRSSI() {
  int rssiA = 0;

  for (uint8_t i = 0; i < RSSI_READS; i++) {
    rssiA += analogRead(rssiPinA);
  }

  rssiA = rssiA / RSSI_READS; // average of RSSI_READS readings
  return rssiA;
}

uint16_t getFilteredRSSI() {
  rssiArr[0] = readRSSI();

  // several-pass filter (need several passes because of integer artithmetics)
  // it reduces possible max value by 1 with each iteration.
  // e.g. if max rssi is 300, then after 5 filter stages it won't be greater than 295
  for (uint8_t i = 1; i <= FILTER_ITERATIONS; i++) {
    rssiArr[i] = (rssiArr[i - 1] + rssiArr[i]) >> 1;
  }

  return rssiArr[FILTER_ITERATIONS];
}

void StartTimer()
{
  Watch = micros(); // get the initial microseconds at the start of the timerreturn
  time = micros(); // hwd added so timer will reset if stopped and then started
  Stop = false;
  Paused = false;
}








int ShowHours()
{
  return Clock / 3600;
}

int ShowMinutes()
{
  return (Clock / 60) % 60;
}

int ShowSeconds()
{
  return Clock % 60;
}








void gameReset()
{
  setupSys = 0;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  FastLED.setBrightness(  BRIGHTNESS );
  clearLeds();
  capStatus = 0;
  capStatusBlue = 0;
  capStatusRed = 0;
  frequency = 0;
  runloop = 0;          // (CC) because I couldn't find any other way to make the code wait after the frequency had been changed I have to run a numeric loop that runs from 0 to 10. At 10 it moves to the next frequency then resets to 0, and runs the loop again.
  runloopsp = 0;
  isBlue = 0;           // Flag is blue
  isRed = 0;            // Flag is red
  pointsRed = 0;
  pointsBlue = 0;
  spCaptured = 0;
  spTimer = 0;
  //spdifficulty = 5000;
  setupSys = 0;
  gameStarted = 0;
  configured = 1;
  Stop = true;
  SetTimer(0, timerMin, timerSec);
  setupRan = true;

  bigMessage = String("");
  smallMessage1 = String("");
  smallMessage2 = String("");

  if (setupSys == 0)
  {
    configured = 0;
  }

}


