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

void deathmatch()
{
  Serial.println(Clock);
  Serial.println(captured);



  if (currPil == 1 && captured != 1 && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      allcolours(whiteLed, pilot1o);
      delay(100);
    }
    captured = 1;

    if (mode == 6 )
      captured = 91;
  }
  else if (currPil == 2 && captured != 2 && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed ; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      allcolours(whiteLed, pilot2o);
      delay(100);
    }
    captured = 2;

    if (mode == 6 )
      captured = 92;
  }

  else  if (currPil == 3 && captured != 3 && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      allcolours(whiteLed, pilot3o);
      delay(100);
    }
    captured = 3;

    if (mode == 6 )
      captured = 93;
  }
  else if (currPil == 4 && captured != 4  && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      allcolours(whiteLed, 4);
      delay(100);
    }
    captured = 4;

    if (mode == 6 )
      captured = 94;
  }
  else if (currPil == 5 && captured != 5  && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      allcolours(whiteLed, pilot5o);
      delay(100);
    }
    captured = 5;

    if (mode == 6 )
      captured = 95;
  }
  else if (currPil == 6 && captured != 6  && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      allcolours(whiteLed, pilot6o);
      delay(100);
    }
    captured = 6;

    if (mode == 6 )
      captured = 96;
  }
  else if (currPil == 7 && captured != 7  && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1 )
    {
      allcolours(whiteLed, pilot7o);
      delay(100);
    }
    captured = 7;

    if (mode == 6 )
      captured = 97;
  }
  else if (currPil == 8 && captured != 8 && captured < 9)
  {
    clearLeds();
    for (byte whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1 )
    {
      allcolours(whiteLed, pilot8o);
      delay(100);
    }
    captured = 8;

    if (mode == 6 )
      captured = 98;
  }
}

