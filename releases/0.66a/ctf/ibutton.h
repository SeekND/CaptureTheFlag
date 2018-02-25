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



float pressLength_milliSeconds = 0;

// Define the *minimum* length of time, in milli-seconds, that the button must be pressed for a particular option to occur
int optionOne_milliSeconds = 100;
int optionTwo_milliSeconds = 1200;
int buttonPin = 3;

int lcd_1key = 0;





void iRSSImenu1()  // white
{
  clearLeds();
  for (int checkingRSSI = 0; checkingRSSI < 20 ; checkingRSSI = checkingRSSI + 1)
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

  for (whiteLed = 0; whiteLed < firstR ; whiteLed = whiteLed + 1)
  {

    delay(600);
    colourGreen();
  }
  whiteLed = 0;
  delay(2000);
  clearLeds();
  for (whiteLed = 0; whiteLed < secondR ; whiteLed = whiteLed + 1)
  {
    delay(600);
    colourGreen();
  }
  whiteLed = 0;
  delay(2000);
  clearLeds();
  for (whiteLed = 0; whiteLed < thirdR ; whiteLed = whiteLed + 1)
  {
    delay(600);
    colourGreen();
  }
  whiteLed = 0;
  delay(2000);
  clearLeds();
  for (whiteLed = 0; whiteLed < 1 ; whiteLed = whiteLed + 1)
  {
    colourWhite();
  }
  whiteLed = 0;
}

void iMODEset() // yellow
{
  clearLeds();
  for (whiteLed = 0; whiteLed < mode ; whiteLed = whiteLed + 1)
  {
    colourGreen();
  }
  whiteLed = 0;
}

void  isingleCTF()   // RED
{
  clearLeds();
  for (whiteLed = 0; whiteLed < spLevel ; whiteLed = whiteLed + 1)
  {
    if ( spLevel  < 3 )
    {
      colourGreen();
    }
    else if ( spLevel  < 5 )
    {
      colourYellow();
    }
    else if ( spLevel  < 7 )
    {
      colourRed();
    }
  }
  whiteLed = 0;
}


void   iPILOTSset()   // BLUE
{
  clearLeds();
  for (whiteLed = 0; whiteLed < numberPilots ; whiteLed = whiteLed + 1)
  {
    colourBlue();
  }
  whiteLed = 0;
}

void iPILOTScolorDM()
{
  clearLeds();
  whiteLed = 0;
  colourBlue();
  whiteLed = 1;
  colourRed();
  whiteLed = 2;
  colourYellow();
  whiteLed = 3;
  colourGreen();
  whiteLed = 4;
  colourPurple();
  whiteLed = 5;
  colourCyan();
  whiteLed = 6;
  colourWhite();
  whiteLed = 7;
  colourBlue();
  delay(1000);
  colourRed();
  delay(1000);
  colourYellow();
  delay(1000);
  colourGreen();
  delay(1000);
  leds[whiteLed] = CRGB::Black;
  FastLED.show();
  whiteLed = 0;
}

void   iPILOTScolor()  // PURPLE
{
  clearLeds();
  if ( pilot1 == 1 && setupSys == 51)
  {
    for (whiteLed = 0; whiteLed < 1 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot1 == 2 && setupSys == 51)
  {
    for (whiteLed = 0; whiteLed < 1 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
  else if ( pilot2 == 1 && setupSys == 52)
  {
    for (whiteLed = 0; whiteLed < 2 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot2 == 2 && setupSys == 52)
  {
    for (whiteLed = 0; whiteLed < 2 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
  else if ( pilot3 == 1 && setupSys == 53)
  {
    for (whiteLed = 0; whiteLed < 3 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot3 == 2 && setupSys == 53)
  {
    for (whiteLed = 0; whiteLed < 3 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
  else if ( pilot4 == 1 && setupSys == 54)
  {
    for (whiteLed = 0; whiteLed < 4 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot4 == 2 && setupSys == 54)
  {
    for (whiteLed = 0; whiteLed < 4 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
  else if ( pilot5 == 1 && setupSys == 55)
  {
    for (whiteLed = 0; whiteLed < 5 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot5 == 2 && setupSys == 55)
  {
    for (whiteLed = 0; whiteLed < 5 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
  else if ( pilot6 == 1 && setupSys == 56)
  {
    for (whiteLed = 0; whiteLed < 6 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot6 == 2 && setupSys == 56)
  {
    for (whiteLed = 0; whiteLed < 6 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
  else if ( pilot7 == 1 && setupSys == 57)
  {
    for (whiteLed = 0; whiteLed < 7 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot7 == 2 && setupSys == 57)
  {
    for (whiteLed = 0; whiteLed < 7 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
  else if ( pilot8 == 1 && setupSys == 58)
  {
    for (whiteLed = 0; whiteLed < 8 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
  }
  else if ( pilot8 == 2 && setupSys == 58)
  {
    for (whiteLed = 0; whiteLed < 8 ; whiteLed = whiteLed + 1)
    {
      colourRed();
    }
  }
}

void igameTimer()   // CYAN - MIN  // BLUE - SEC
{
  clearLeds();
  for (whiteLed = 0; whiteLed < timerMin ; whiteLed = whiteLed + 1)
  {
    colourCyan();
  }
  whiteLed = 0;
  if ( timerSec == 30)
  {
    for (whiteLed = 0; whiteLed < 1 ; whiteLed = whiteLed + 1)
    {
      colourBlue();
    }
    whiteLed = 0;
  }
}




void buttonShort()
{
  if (setupSys == 11) // does autorssi - will show green light when done
  {
    iRSSImenu1();
  }
  else if (setupSys == 21 ) // set modes
  {
    if ( mode < 5 )
    {
      mode++;
      iMODEset();
    }
    else if ( mode == 5 )
    {
      mode = 2;
      iMODEset();
    }
  }
  else if (setupSys == 31 ) // dificulty for SP OR number of pilots
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
  else if (setupSys > 50 && setupSys < 59 ) // number of leds
  {
    if (setupSys == 51 && mode != 5 && mode != 4)
    {
      if ( pilot1 == 1 )
      {
        pilot1 = 2;
      }
      else
        pilot1 = 1;
    }
    else if (setupSys == 52)
    {
      if ( pilot2 == 1 )
      {
        pilot2 = 2;
      }
      else
        pilot2 = 1;
    }

    else if (setupSys == 53)
    {
      if ( pilot3 == 1 )
      {
        pilot3 = 2;
      }
      else
        pilot3 = 1;
    }

    else if (setupSys == 54)
    {
      if ( pilot4 == 1 )
      {
        pilot4 = 2;
      }
      else
        pilot4 = 1;
    }

    else if (setupSys == 55)
    {
      if ( pilot5 == 1 )
      {
        pilot5 = 2;
      }
      else
        pilot5 = 1;
    }
    else if (setupSys == 56)
    {
      if ( pilot6 == 1 )
      {
        pilot6 = 2;
      }
      else
        pilot6 = 1;
    }

    else if (setupSys == 57)
    {
      if ( pilot7 == 1 )
      {
        pilot7 = 2;
      }
      else
        pilot7 = 1;
    }

    else if (setupSys == 58)
    {
      if ( pilot8 == 1 )
      {
        pilot8 = 2;
      }
      else
        pilot8 = 1;
    }
    iPILOTScolor();
  }
  else if (setupSys == 61 ) // colours of pilots
  {

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
  Serial.println(spLevel);
}



void buttonLong()
{
  if (configured == 2)
  {
    configured = 0;
    gameReset();
    setupSys = 11;
    for (whiteLed = 0; whiteLed < 1; whiteLed = whiteLed + 1)
    {
      colourWhite();
    }
  }
  /*  if (setupSys == 0)
    {
      if ( configured == 1)
      {
        configured = 2;

        smallMessage1 = "";
        smallMessage2 = "";
        setupSys = 99;
      }
      else if ( configured == 0)  // moves to next menu >> RSSI
      {
        clearLeds();

        configured = 3;
        setupSys = 11;
        colourWhite();

      }

    }*/
  else if (setupSys == 11)  // moves to next menu >> MODE
  {
    iMODEset();
    setupSys = 21;


  }
  else if (setupSys == 21)  // moves to PILOTS
  {
    if ( mode == 4 )
    {
      isingleCTF();
      setupSys = 31;
    }
    else
    {
      iPILOTSset();
      setupSys = 31;
    }
  }
  else if (setupSys == 31) // moves to NUMBERLEDS
  {
    if ( mode == 4 )
    {
      igameTimer();
      setupSys = 71;
    }
    else if (mode == 5)
    {
      iPILOTScolorDM();
      setupSys = 51;
    }
    else
    {
      iPILOTScolor();
      setupSys = 51;
    }
  }
  else if (setupSys > 50 && setupSys < 59 ) // moves to NUMBERLEDS
  {
    if (mode == 5)
    {
      igameTimer();
      setupSys = 71;
    }
    else if (setupSys - 50 == numberPilots)
    {
      igameTimer();
      setupSys = 71;
    }
    else if ( setupSys != 59 )
    {
      setupSys++;
      iPILOTScolor();
    }
  }
  else if (setupSys == 71) // Finished, will start game
  {
    clearLeds();
    smallMessage1 = "";
    smallMessage2 = "";
    setupSys = 99;
    configured = 2;
  }
}



int  read_1_button()
{

  while (digitalRead(buttonPin) == LOW ) {
    delay(100);  //if you want more resolution, lower this number
    pressLength_milliSeconds = pressLength_milliSeconds + 100;
  }

  if (pressLength_milliSeconds >= optionTwo_milliSeconds) {

    buttonLong();
  }
  else if (pressLength_milliSeconds >= optionOne_milliSeconds) {

    buttonShort();
  }


  //every time through the loop, we need to reset the pressLength_Seconds counter
  pressLength_milliSeconds = 0;
}








