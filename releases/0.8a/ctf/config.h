/**
   CTF code by Carlos Costa (SeekNDFPV @ youtube)
   Base RSSI checker code by Andrey Voroshkov (bshep)
   SPI driver based on fs_skyrf_58g-main.c by Simon Chambers
   fast ADC reading code is by "jmknapp" from Arduino forum
   fast port I/O code from http://masteringarduino.blogspot.com.by/2013/10/fastest-and-smallest-digitalread-and.html


  The MIT License (MIT)

  Copyright (c) 2018 by Carlos Costa (SeekND FPV)

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
  clearLeds();
  captured = 0;
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
  currPil = 1;
  setupSys = 0;
  gameStarted = 0;
  configured = 1;
  Stop = true;
  SetTimer(0, timerMin, timerSec);
  setupRan = true;

  bigMessage = "";
  smallMessage1 = "";
  smallMessage2 = "";

  if (haveexternalleds == false )  // just in case you put some extra leds but forgot to change the values
  {
    startfromLed = 0;
    externalLeds = 0;
  }
  else if ( haveexternalleds == true )
  {
    startfromLed = internalLeds;
  }

  if (setupSys == 0)
  {
    configured = 0;
  }

}



void modeShow()
{
  if  ( mode == 2 )
  {
    smallMessage1 =  "CTF ";
  }
  else if  ( mode == 3 )
  {
    smallMessage1 =  "DOM CTF";
  }
  else if  ( mode == 4 )
  {
    smallMessage1 =  "SP CTF";
  }
  else if  ( mode == 5 )
  {
    smallMessage1 =  "DM";
  }
  else if  ( mode == 6 )
  {
    smallMessage1 =  "HUNT";
  }
}

void MODEset()
{

  bigMessage = "MODE";
  modeShow();
  smallMessage2 = "";
}



boolean TimeHasChanged()
{
  return timeFlag;
}

// output true if timer equals requested time
boolean TimeCheck(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
  return ( minutes == ShowMinutes() && seconds == ShowSeconds());
}


boolean CountDownTimer()
{
  static unsigned long duration = 1000000; // 1 second
  timeFlag = false;

  if (!Stop && !Paused) // if not Stopped or Paused, run timer
  {
    // check the time difference and see if 1 second has elapsed
    if ((_micro = micros()) - time > duration )
    {
      Clock--;
      timeFlag = true;

      if (Clock == 0 || spCaptured == 3) // check to see if the clock is 0
      {

        Stop = true; // If so, stop the timer
        clearLeds();
        for (int i = 0; i < (internalLeds + externalLeds) * 5; i++) {

          static uint8_t hue = 0;
          for (int i = startfromLed; i < internalLeds + externalLeds; i++) {

            leds[i] = CHSV(hue++, 255, 255);
            FastLED.show();
            for (int i = 0; i < internalLeds + externalLeds; i++) {
              leds[i].nscale8(250);
            }
            delay(10);
          }
          for (int i = (internalLeds + externalLeds) - 1; i >= 0; i--) {

            leds[i] = CHSV(hue++, 255, 255);
            FastLED.show();
            for (int i = 0; i < internalLeds + externalLeds; i++) {
              leds[i].nscale8(250);
            }
            delay(10);
          }
        }
        clearLeds();
        bigMessage = "END";


        if ( haveexternalleds == true ) {
          startfromLed = internalLeds;
        }


        if (pointsRed < pointsBlue && mode != 4 )
        {
          for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
          {
            colourBlue(whiteLed);
          }
          smallMessage1 = String(pointsBlue) + String("  "); // makes no sense but I can't take the second string out otherwise the program fails

        }
        else if ( pointsRed > pointsBlue && mode != 4 )
        {
          for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
          {
            colourRed(whiteLed);
          }
          smallMessage1 =  String(pointsRed);
        }
        else
        {

          if (pointsBlue > 250 * internalLeds)
          {
            ledsUp = internalLeds + externalLeds - startfromLed;
          }
          else
          {
            ledsUp = pointsBlue / 250;
            ledsUp++;
          }

          for (byte whiteLed = startfromLed; whiteLed < ledsUp ; whiteLed = whiteLed + 1)
          {
            if (spCaptured == 3)
            {
              colourRed(whiteLed);
            }
            else if ( captured > 0 )
            {
              if ( captured > 90 )
                captured = captured - 90;

              if ( captured == 1)
                captured = pilot1o;
              else if ( captured == 2)
                captured = pilot2o;
              else if ( captured == 3)
                captured = pilot3o;
              else if ( captured == 4)
                captured = pilot4o;
              else if ( captured == 5)
                captured = pilot5o;
              else if ( captured == 6)
                captured = pilot6o;
              else if ( captured == 7)
                captured = pilot7o;
              else if ( captured == 8)
                captured = pilot8o;

              allcolours(gamesPlayed - 1 , captured);
            }
            else
            {
              colourYellow(whiteLed);
            }
          }
          if (mode == 4)
          {
            bigMessage = "END";
          }
          else
          {
            bigMessage = "TIE";
          }
          smallMessage1 =  String(pointsBlue);
        }
        if (mode == 4 )
          delay( ( (timerMin * 60000) + (timerSec * 1000) ) / 4);
        else
          delay( ( (timerMin * 60000) + (timerSec * 1000) ) / 2);

        if (gamesPlayed < internalLeds + externalLeds)
        {
          gamesPlayed++;
        }
        else
        {
          gamesPlayed = 1;
        }

        gameReset();
        configured = 2;

      }

      // check to see if micros() has rolled over, if not,
      // then increment "time" by duration
      _micro < time ? time = _micro : time += duration;
    }
  }
  return !Stop; // return the state of the timer
}

int spdifficultysetting()
{
  if ( haveexternalleds == true )
  {
    spdifficulty = externalLeds * 10 / spLevel * 20;

  }
  else if ( haveexternalleds == false )
  {
    spdifficulty = internalLeds * 10 / spLevel * 20;
  }
}




// -------OTHER SETUPS --------------------------------


// ----------------------------------------------------------------------------
uint16_t setRssiMonitorDelay(uint16_t delay) {
  return delay < MIN_RSSI_MONITOR_DELAY_CYCLES ? MIN_RSSI_MONITOR_DELAY_CYCLES : delay;
}
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
uint16_t getMedian(uint16_t a[], uint16_t size) {
  return a[size / 2];
}

