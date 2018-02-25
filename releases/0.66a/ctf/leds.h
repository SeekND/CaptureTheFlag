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

void clearLeds()
{

  for (whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Black;
    FastLED.show();
  }

}


void lightsReady()
{

  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Red;
    FastLED.show();
    delay(50);
  }
  clearLeds();
}

void colourBlue()
{
  leds[whiteLed] = CRGB::Blue;
  FastLED.show();
}

void colourRed()
{
  leds[whiteLed] = CRGB::Green;
  FastLED.show();
}


void colourGreen()
{
  leds[whiteLed] = CRGB::Red;
  FastLED.show();
}


void colourYellow()
{
  leds[whiteLed] = CRGB::Yellow;
  FastLED.show();
}


void colourWhite()
{
  leds[whiteLed] = CRGB::Gray;
  FastLED.show();
}

void colourCyan()
{
  leds[whiteLed] = CRGB::Cyan;
  FastLED.show();
}

void colourPurple()
{
  leds[whiteLed] = CRGB::Purple;
  FastLED.show();
}

void colourMulti()
{
  byte part1 = (internalLeds + externalLeds) / 5;
  byte part2 = (internalLeds + externalLeds) / 5;
  byte part3 = (internalLeds + externalLeds) / 5;
  byte part4 = (internalLeds + externalLeds) / 5;
  byte part5 = (internalLeds + externalLeds) / 5;
  leds[part1] = CRGB::Blue; // need to find another colour
  FastLED.show();
  delay(500);
  leds[part1 + part2] = CRGB::Red; // need to find another colour
  FastLED.show();
  delay(500);
  leds[part1 + part2 + part3] = CRGB::Green; // need to find another colour
  FastLED.show();
  delay(500);
  leds[part1 + part2 + part3 + part4] = CRGB::Yellow; // need to find another colour
  FastLED.show();
  delay(500);
  leds[part1 + part2 + part3 + part4 + part5] = CRGB::Yellow; // need to find another colour
  FastLED.show();
  delay(500);
}

void confirmBlue()
{
  clearLeds();
  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Blue;
    FastLED.show();
    delay(100);
  }
}



void confirmRed()
{
  clearLeds();
  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Green;
    FastLED.show();
    delay(100);
  }
}

void ledsBlue()
{
  leds[capStatusBlue + externalLeds] = CRGB::Blue;
  FastLED.show();
  capStatusBlue++;
  delay(1000);
}

void ledsRed()
{
  leds[capStatusRed + externalLeds] = CRGB::Green;
  FastLED.show();
  capStatusRed++;
  delay(1000);
}


void ledsBluesimple()
{
  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Blue;
    FastLED.show();
    delay(500);
  }
}

void ledsRedsimple()
{
  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Green;
    FastLED.show();
    delay(500);
  }
}

void bluecapped()
{
  if (capStatusBlue + externalLeds < internalLeds + externalLeds ) // was NUM_LEDS before
  {
    isRed = 0;
    capStatusRed = 0;
    ledsBlue();
  }
  else
  {
    capStatusBlue = 0;
    isBlue = 1;
    pointsBlue++;
    confirmBlue();
  }
}

void redcapped()
{
  if (capStatusRed + externalLeds < internalLeds + externalLeds ) // was NUM_LEDS before
  {
    isBlue = 0;
    capStatusBlue = 0;
    ledsRed();
  }
  else
  {
    capStatusRed = 0;
    isRed = 1;
    pointsRed++;

    confirmRed();
  }
}






void checkBlueRedsimple()
{
  if ( pilot1 == 1 && isBlue == 0 && channelIndex == 0 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot1 == 2 && isRed == 0 && channelIndex == 0 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot2 == 1 && isBlue == 0 && channelIndex == 1 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot2 == 2 && isRed == 0 && channelIndex == 1 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot3 == 1 && isBlue == 0 && channelIndex == 2 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot3 == 2 && isRed == 0 && channelIndex == 2 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot4 == 1 && isBlue == 0 && channelIndex == 3 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot4 == 2 && isRed == 0 && channelIndex == 3 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot5 == 1 && isBlue == 0 && channelIndex == 4 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot5 == 2 && isRed == 0 && channelIndex == 4 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot6 == 1 && isBlue == 0 && channelIndex == 5 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot6 == 2 && isRed == 0 && channelIndex == 5 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot7 == 1 && isBlue == 0 && channelIndex == 6 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot7 == 2 && isRed == 0 && channelIndex == 6 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot8 == 1 && isBlue == 0 && channelIndex == 7 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot8 == 2 && isRed == 0 && channelIndex == 7 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
}

