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

void clearLeds()
{

  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Black;
    FastLED.show();
  }

}



void colourBlue(byte timesLed)
{
  leds[timesLed] = CRGB::Blue;
  FastLED.show();
}

void colourRed(byte timesLed)
{
  leds[timesLed] = CRGB::Red;
  FastLED.show();
}


void colourGreen(byte timesLed)
{
  leds[timesLed] = CRGB::Green;
  FastLED.show();
}


void colourYellow(byte timesLed)
{
  leds[timesLed] = CRGB::Yellow;
  FastLED.show();
}


void colourWhite(byte timesLed)
{
  leds[timesLed] = CRGB::White;
  FastLED.show();
}

void colourCyan(byte timesLed)
{
  leds[timesLed] = CRGB::Cyan;
  FastLED.show();
}

void colourPurple(byte timesLed)
{
  leds[timesLed] = CRGB::Purple;
  FastLED.show();
}

void colourOrange(byte timesLed)
{
  leds[timesLed] = CRGB::Orange;
  FastLED.show();
}

void allcolours(byte timesLed , byte pilot)
{
  if ( pilot == 1)
  {
    colourBlue(timesLed);
  }
  else if ( pilot == 2)
  {
    colourRed(timesLed);
  }
  else if ( pilot == 3)
  {
    colourGreen(timesLed);
  }
  else if ( pilot == 4)
  {
    colourYellow(timesLed);
  }
  else if ( pilot == 5)
  {
    colourPurple(timesLed);
  }
  else if ( pilot == 6)
  {
    colourCyan(timesLed);
  }
  else if ( pilot == 7)
  {
    colourWhite(timesLed);
  }
  else if ( pilot == 8)
  {
    colourOrange(timesLed);
  }
}



void confirmBlue()
{
  clearLeds();
  for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    colourBlue(whiteLed);
    delay(100);
  }
}

void confirmRed()
{
  clearLeds();
  for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    colourRed(whiteLed);
    delay(100);
  }
}

void ledsBlue()
{
  clearLeds();
  for (byte whiteLed = startfromLed; whiteLed < capStatusBlue + externalLeds; whiteLed = whiteLed + 1)
  {
    colourBlue(whiteLed);
  }
  capStatusBlue++;
}

void ledsRed()
{

  clearLeds();
  for (byte whiteLed = startfromLed; whiteLed < capStatusRed + externalLeds; whiteLed = whiteLed + 1)
  {
    colourRed(whiteLed);
  }
  capStatusRed++;
}


void ledsBluesimple()
{
  for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    colourBlue(whiteLed);
    delay(250);
  }
}

void ledsRedsimple()
{
  for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    colourRed(whiteLed);
    delay(250);
  }
}








void checkBlueRedsimple()
{
  if ( pilot1 == 1 && isBlue == 0 && currPil == 1 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot1 == 2 && isRed == 0 && currPil == 1 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot2 == 1 && isBlue == 0 && currPil == 2 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot2 == 2 && isRed == 0 && currPil == 2 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot3 == 1 && isBlue == 0 && currPil == 3 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot3 == 2 && isRed == 0 && currPil == 3 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot4 == 1 && isBlue == 0 && currPil == 4 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot4 == 2 && isRed == 0 && currPil == 4 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot5 == 1 && isBlue == 0 && currPil == 5 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot5 == 2 && isRed == 0 && currPil == 5 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot6 == 1 && isBlue == 0 && currPil == 6 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot6 == 2 && isRed == 0 && currPil == 6 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot7 == 1 && isBlue == 0 && currPil == 7)
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot7 == 2 && isRed == 0 && currPil == 7 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot8 == 1 && isBlue == 0 && currPil == 8 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot8 == 2 && isRed == 0 && currPil == 8 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
}


void lightsReady()
{

  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    colourGreen(whiteLed);
    delay(50);
  }
  clearLeds();
}

