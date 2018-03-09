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



float pressLength_milliSeconds = 0;

// Define the *minimum* length of time, in milli-seconds, that the button must be pressed for a particular option to occur
int optionOne_milliSeconds = 100;
int optionTwo_milliSeconds = 1200;
int optionThree_milliSeconds = 5000;
int optionFour_milliSeconds = 10000;

int lcd_1key = 0;





void iRSSImenu1()  // white
{
  clearLeds();
  for (byte checkingRSSI = 0; checkingRSSI < 20 ; checkingRSSI = checkingRSSI + 1)
  {
    channelIndex = 0;
    frequency = setModuleChannel(channelIndex, bandIndex);
    rssiThreshold = getFilteredRSSI();
  }

  rssiThreshold = rssiThreshold - 10;

  int firstR = rssiThreshold / 100;
  int secondR = (rssiThreshold - firstR * 100) / 10;
  int thirdR = rssiThreshold - (firstR * 100) - (secondR * 10);

  if ( firstR == 0 )
  {
    firstR = 1;
  }
  if ( secondR == 0 )
  {
    secondR = 1;
  }
  if ( thirdR == 0 )
  {
    thirdR = 1;
  }

  for (byte whiteLed = 0; whiteLed < firstR ; whiteLed = whiteLed + 1)
  {

    delay(600);
    colourGreen(whiteLed);
  }
  delay(2000);
  clearLeds();
  for (byte whiteLed = 0; whiteLed < secondR ; whiteLed = whiteLed + 1)
  {
    delay(600);
    colourGreen(whiteLed);
  }
  delay(2000);
  clearLeds();
  for (byte whiteLed = 0; whiteLed < thirdR ; whiteLed = whiteLed + 1)
  {
    delay(600);
    colourGreen(whiteLed);
  }

  delay(2000);
  clearLeds();
  for (byte whiteLed = 0; whiteLed < 1 ; whiteLed = whiteLed + 1)
  {
    colourWhite(whiteLed);
  }

}

void iMODEshow() // yellow
{
  clearLeds();
  for (byte whiteLed = 0; whiteLed < mode ; whiteLed = whiteLed + 1)
  {
    colourWhite(whiteLed);
  }
}

void pilotFreqs()
{
  clearLeds();
  for (byte whiteLed = 0; whiteLed < channelIndex + 1 ; whiteLed = whiteLed + 1)
  {
    if ( bandIndex == 0)
    {
      colourBlue(whiteLed);
    }
    else if ( bandIndex == 1)
    {
      colourRed(whiteLed);
    }
    else if ( bandIndex == 2)
    {
      colourYellow(whiteLed);
    }
    else if ( bandIndex == 3)
    {
      colourGreen(whiteLed);
    }
    else if ( bandIndex == 4)
    {
      colourPurple(whiteLed);
    }
    else if ( bandIndex == 5)
    {
      colourCyan(whiteLed);
    }
  }
}

void  isingleCTF()   // RED
{
  clearLeds();
  for (byte whiteLed = 0; whiteLed < spLevel ; whiteLed = whiteLed + 1)
  {
    if ( spLevel  < 3 )
    {
      colourGreen(whiteLed);
    }
    else if ( spLevel  < 5 )
    {
      colourYellow(whiteLed);
    }
    else if ( spLevel  < 7 )
    {
      colourRed(whiteLed);
    }
  }
}


void   iPILOTSset()   // BLUE
{
  clearLeds();
  for (byte whiteLed = 0; whiteLed < numberPilots ; whiteLed = whiteLed + 1)
  {
    colourBlue(whiteLed);
  }
}

void   iPILOTScolor()  // PURPLE
{
  clearLeds();

  if ( mode == 5 || mode == 6 )
  {
    if ( setupSys == 21) {
      allcolours(setupSys - 21, pilot1o);
    }
    else if ( setupSys == 22) {
      allcolours(setupSys - 21, pilot2o);
    }
    else if ( setupSys == 23) {
      allcolours(setupSys - 21, pilot3o);
    }
    else if ( setupSys == 24) {
      allcolours(setupSys - 21, pilot4o);
    }
    else if ( setupSys == 25) {
      allcolours(setupSys - 21, pilot5o);
    }
    else if ( setupSys == 26) {
      allcolours(setupSys - 21, pilot6o);
    }
    else if ( setupSys == 27) {
      allcolours(setupSys - 21, pilot7o);
    }
    else if ( setupSys == 28) {
      allcolours(setupSys - 21, pilot8o);
    }

  }
  else
  {
    if ( setupSys == 21) {
      allcolours(setupSys - 21, pilot1);
    }
    else if ( setupSys == 22) {
      allcolours(setupSys - 21, pilot2);
    }
    else if ( setupSys == 23) {
      allcolours(setupSys - 21, pilot3);
    }
    else if ( setupSys == 24) {
      allcolours(setupSys - 21, pilot4);
    }
    else if ( setupSys == 25) {
      allcolours(setupSys - 21, pilot5);
    }
    else if ( setupSys == 26) {
      allcolours(setupSys - 21, pilot6);
    }
    else if ( setupSys == 27) {
      allcolours(setupSys - 21, pilot7);
    }
    else if ( setupSys == 28) {
      allcolours(setupSys - 21, pilot8);
    }
  }


}

void igameTimer()   // Purple - MIN  // BLUE - SEC
{
  clearLeds();
  for (byte whiteLed = 0; whiteLed < timerMin ; whiteLed = whiteLed + 1)
  {
    colourPurple(whiteLed);
  }

  if ( timerSec == 30)
  {
    for (byte whiteLed = 0; whiteLed < 1 ; whiteLed = whiteLed + 1)
    {
      colourBlue(whiteLed);
    }

  }
}




void buttonShort()
{
  if (setupSys == 1) // nr pilots
  {
    if ( BRIGHTNESS < 120 )
    {
      BRIGHTNESS = BRIGHTNESS + 10 ;
    }
    else// if ( BRIGHTNESS == 120 )
    {
      BRIGHTNESS = 10;
    }
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::White;
      FastLED.setBrightness( BRIGHTNESS );
      FastLED.show();
    }
  }
  else if (setupSys == 2) //main lights only or extra lights
  {
    clearLeds();
    if ( haveexternalleds == false )
    {
      haveexternalleds = true;
      startfromLed = internalLeds;
      if ( externalLeds == 0 )
        externalLeds = 1;

      for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
      {
        colourRed(whiteLed);
      }
    }
    else
    {
      haveexternalleds = false;
      startfromLed = 0;
      externalLeds=0;

      for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
      {
        colourBlue(whiteLed);
      }
    }
  }
  else if (setupSys == 3) // extra lights number
  {
    clearLeds();
    if ( internalLeds + externalLeds < NUM_LEDS)
    {
      externalLeds++;
    }
    else
    {
      externalLeds = 1;
    }
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      colourRed(whiteLed);
    }
  }
  else if (setupSys == 9) // sets modes
  {
    if ( mode < 6 )
    {
      mode++;
      iMODEshow();
    }
    else if ( mode == 6 )
    {
      mode = 2;
      iMODEshow();
    }
  }
  else if (setupSys == 11 ) // dificulty for SP OR number of pilots
  {
    if ( mode == 4 )
    {
      if ( spLevel < 6 )
      {
        spLevel++;
        isingleCTF();
      }
      else
      {
        spLevel = 1;
        isingleCTF();
      }
    }
    else
    {
      if ( numberPilots < 8 )
      {
        numberPilots++;
        iPILOTSset();
      }
      else
      {
        numberPilots = 1;
        iPILOTSset();
      }
    }
  }
  else if (setupSys > 20 && setupSys < 29 ) // pilot colour
  {
    byte pca = numberPilots;
    if (mode == 5 || mode == 6 )
    {
      pca = 8;

      if (setupSys == 21)
      {
        if (pilot1o < pca)
        {
          pilot1o++;
        }
        else
        {
          pilot1o = 1;
        }

      }
      else if (setupSys == 22)
      {

        if (pilot2o < pca)
        {
          pilot2o++;
        }
        else
        {
          pilot2o = 1;
        }
      }

      else if (setupSys == 23)
      {

        if (pilot3o < pca)
        {
          pilot3o++;
        }
        else
        {
          pilot3o = 1;
        }
      }

      else if (setupSys == 24)
      {
        if (pilot4o < pca)
        {
          pilot4o++;
        }
        else
        {
          pilot4o = 1;
        }
      }

      else if (setupSys == 25)
      {
        if (pilot5o < pca)
        {
          pilot5o++;
        }
        else
        {
          pilot5o = 1;
        }
      }
      else if (setupSys == 26)
      {
        if (pilot6o < pca)
        {
          pilot6o++;
        }
        else
        {
          pilot6o = 1;
        }

      }

      else if (setupSys == 27)
      {
        if (pilot7o < pca)
        {
          pilot7o++;
        }
        else
        {
          pilot7o = 1;
        }
      }

      else if (setupSys == 28)
      {
        if (pilot8o < pca)
        {
          pilot8o++;
        }
        else
        {
          pilot8o = 1;
        }
      }
    }
    else
    {
      pca = 2; // number of colours you can set

      if (setupSys == 21)
      {
        if (pilot1 < pca)
        {
          pilot1++;
        }
        else
        {
          pilot1 = 1;
        }

      }
      else if (setupSys == 22)
      {

        if (pilot2 < pca)
        {
          pilot2++;
        }
        else
        {
          pilot2 = 1;
        }
      }

      else if (setupSys == 23)
      {

        if (pilot3 < pca)
        {
          pilot3++;
        }
        else
        {
          pilot3 = 1;
        }
      }

      else if (setupSys == 24)
      {
        if (pilot4 < pca)
        {
          pilot4++;
        }
        else
        {
          pilot4 = 1;
        }
      }

      else if (setupSys == 25)
      {
        if (pilot5 < pca)
        {
          pilot5++;
        }
        else
        {
          pilot5 = 1;
        }
      }
      else if (setupSys == 26)
      {
        if (pilot6 < pca)
        {
          pilot6++;
        }
        else
        {
          pilot6 = 1;
        }

      }

      else if (setupSys == 27)
      {
        if (pilot7 < pca)
        {
          pilot7++;
        }
        else
        {
          pilot7 = 1;
        }
      }

      else if (setupSys == 28)
      {
        if (pilot8 < pca)
        {
          pilot8++;
        }
        else
        {
          pilot8 = 1;
        }

      }
    }

    iPILOTScolor();
  }
  else if (setupSys > 30 && setupSys < 39 ) // pilot freqs
  {
    if (channelIndex < 7)
    {
      channelIndex++;
    }
    else
    {
      if (bandIndex < 5)
      {
        bandIndex++;
        channelIndex = 0;
      }
      else
      {
        bandIndex = 0;
        channelIndex = 0;
      }
    }
    if (setupSys == 31)
    {
      chanP1 = channelIndex;
      bandP1 = bandIndex;
    }
    else if (setupSys == 32)
    {
      chanP2 = channelIndex;
      bandP2 = bandIndex;
    }
    else if (setupSys == 33)
    {
      chanP3 = channelIndex;
      bandP3 = bandIndex;
    }
    else if (setupSys == 34)
    {
      chanP4 = channelIndex;
      bandP4 = bandIndex;
    }
    else if (setupSys == 35)
    {
      chanP5 = channelIndex;
      bandP5 = bandIndex;
    }
    else if (setupSys == 36)
    {
      chanP6 = channelIndex;
      bandP6 = bandIndex;
    }
    else if (setupSys == 37)
    {
      chanP7 = channelIndex;
      bandP7 = bandIndex;
    }
    else if (setupSys == 37)
    {
      chanP8 = channelIndex;
      bandP8 = bandIndex;
    }
    frequency = setModuleChannel(channelIndex, bandIndex);
    pilotFreqs();
  }

  else if (setupSys == 41 ) // does autorssi - will show white light when done
  {
    clearLeds();
    delay(2000);
    iRSSImenu1();
  }

  else if (setupSys == 71 ) // game timer
  {
    if ( timerMin > internalLeds + externalLeds - 1 )
    {
      timerSec = 0;
      timerMin = 1;
    }
    else if ( timerSec == 30 && timerMin < internalLeds + externalLeds )
    {
      timerSec = 0;
      timerMin++;
    }
    else if (timerSec == 0 && timerMin < internalLeds + externalLeds)
    {
      timerSec = 30;
    }


    igameTimer();
  }
}

void buttonLongest()
{
  clearLeds();

  configured = 0;
  gameReset();
  setupSys = 1;
  for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
  {
    colourWhite(whiteLed);
  }

}

void buttonLong()
{
  clearLeds();
  if (configured == 2)  // gets into setup - moves to moves
  {
    configured = 0;
    gameReset();
    setupSys = 41;
    colourWhite(0);

    channelIndex = chanP1;
    bandIndex = bandP1;
    frequency = setModuleChannel(channelIndex, bandIndex);
  }
  else if ( setupSys == 1) // is brightness >> moves to main or external lights on
  {
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      colourBlue(whiteLed);
    }
    setupSys = 2;
  }
  else if ( setupSys == 2)  // main lights on or external >> moves to number lights or main setup
  {
    if (  haveexternalleds == true )
    {
      for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
      {
        colourRed(whiteLed);
      }
      setupSys = 3;
    }
    else
    {
      iMODEshow();
      setupSys = 9;
    }
  }
  else if ( setupSys == 3)  // is main lights  >> moves to player lights or brightness
  {
    setupSys = 9;
    iMODEshow();
  }
  else if (setupSys == 9)  // is modes >> moves to moves to pilot nr
  {
    if ( mode == 4 )
    {
      isingleCTF();
      setupSys = 11;
    }
    else
    {
      iPILOTSset();
      setupSys = 11;
    }
  }
  else if (setupSys == 11) // is pilot nr >> moves to colours
  {


    if (mode == 4)  // is pilot nr >> moves to freqs
    {
      setupSys = 31;

      channelIndex = chanP1;
      bandIndex = bandP1;
      frequency = setModuleChannel(channelIndex, bandIndex);
      colourWhite(0);
      delay(1000);
      pilotFreqs();
    }
    else
    {
      setupSys = 21;
      iPILOTScolor();
    }
  }
  else if (setupSys > 20 && setupSys < 29 ) // is colours >> moves to freq
  {

    if (setupSys - 20 == numberPilots)
    {
      setupSys = 31;

      channelIndex = chanP1;
      bandIndex = bandP1;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(0);
      delay(1000);
      pilotFreqs();

    }
    else if ( setupSys != 29 )
    {
      setupSys++;
      iPILOTScolor();
    }
  }

  else if (setupSys > 30 && setupSys < 39)  // if freq >> moves to PILOTS
  {


    if (mode == 4)
    {
      chanP1 = channelIndex;
      bandP1 = bandIndex;

      colourWhite(0);
      setupSys = 41;
    }
    else if (setupSys == 31 && numberPilots > setupSys - 30)
    {
      chanP1 = channelIndex;
      bandP1 = bandIndex;
      channelIndex = chanP2;
      bandIndex = bandP2;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(1);
      delay(1000);
      pilotFreqs();
      setupSys++;
    }
    else if  (setupSys == 32 && numberPilots > setupSys - 30)
    {
      chanP2 = channelIndex;
      bandP2 = bandIndex;
      channelIndex = chanP3;
      bandIndex = bandP3;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(2);
      delay(1000);
      pilotFreqs();
      setupSys++;
    }
    else if  (setupSys == 33 && numberPilots > setupSys - 30)
    {
      chanP3 = channelIndex;
      bandP3 = bandIndex;
      channelIndex = chanP4;
      bandIndex = bandP4;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(3);
      delay(1000);
      pilotFreqs();
      setupSys++;
    }
    else if  (setupSys == 34 && numberPilots > setupSys - 30)
    {
      chanP4 = channelIndex;
      bandP4 = bandIndex;
      channelIndex = chanP5;
      bandIndex = bandP5;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(4);
      delay(1000);
      pilotFreqs();
      setupSys++;
    }
    else if  (setupSys == 35 && numberPilots > setupSys - 30)
    {
      chanP5 = channelIndex;
      bandP5 = bandIndex;
      channelIndex = chanP6;
      bandIndex = bandP6;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(5);
      delay(1000);
      pilotFreqs();
      setupSys++;
    }

    else if  (setupSys == 36 && numberPilots > setupSys - 30)
    {
      chanP6 = channelIndex;
      bandP6 = bandIndex;
      channelIndex = chanP7;
      bandIndex = bandP7;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(6);
      delay(1000);
      pilotFreqs();
      setupSys++;
    }
    else if  (setupSys == 37 && numberPilots > setupSys - 30)
    {
      chanP7 = channelIndex;
      bandP7 = bandIndex;
      channelIndex = chanP8;
      bandIndex = bandP8;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(7);
      delay(1000);
      pilotFreqs();
      setupSys++;
    }

    else if  (setupSys == 38 && numberPilots > setupSys - 30)
    {
      chanP8 = channelIndex;
      bandP8 = bandIndex;
      channelIndex = chanP1;
      bandIndex = bandP1;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(0);
      setupSys = 41;
    }
    else
    {
      channelIndex = chanP1;
      bandIndex = bandP1;
      frequency = setModuleChannel(channelIndex, bandIndex);

      colourWhite(0);
      setupSys = 41;
    }
  }
  else if (setupSys == 41) // is RSSI >> moves to timer
  {
    setupSys = 71;
    igameTimer();
  }
  else if (setupSys == 71) // is timer >> when pressed it will finish & will start game
  {
    smallMessage1 = "";
    smallMessage2 = "";
    setupSys = 99;
    configured = 2;
  }
}

void buttonLonger()
{
  clearLeds();

  configured = 0;
  gameReset();
  setupSys = 9;
  iMODEshow();

}

int  read_1_button()
{

  while (digitalRead(buttonPin) == LOW ) {
    delay(100);  //if you want more resolution, lower this number
    pressLength_milliSeconds = pressLength_milliSeconds + 100;
  }
  if (pressLength_milliSeconds >= optionFour_milliSeconds) {

    buttonLongest();
  }
  else if (pressLength_milliSeconds >= optionThree_milliSeconds) {

    buttonLonger();
  }
  else if (pressLength_milliSeconds >= optionTwo_milliSeconds) {

    buttonLong();
  }
  else if (pressLength_milliSeconds >= optionOne_milliSeconds) {

    buttonShort();
  }


  //every time through the loop, we need to reset the pressLength_Seconds counter
  pressLength_milliSeconds = 0;
}








