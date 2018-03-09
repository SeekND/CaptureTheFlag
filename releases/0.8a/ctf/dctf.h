/*
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


void bluecapped()
{
  if (capStatusBlue + externalLeds < internalLeds + externalLeds && isBlue != 1)
  {
    isRed = 0;
    capStatusRed = 0;
    ledsBlue();
    delay(500);
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
  if (capStatusRed + externalLeds < internalLeds + externalLeds  && isRed != 1 )
  {
    isBlue = 0;
    capStatusBlue = 0;
    ledsRed();
    delay(500);
  }
  else
  {
    capStatusRed = 0;
    isRed = 1;
    pointsRed++;

    confirmRed();
  }
}

void dctf()
{
  if ( pilot1 == 1 && currPil == 1 && isBlue == 0 )
  {
    bluecapped();
  }
  else if ( pilot1 == 2 && currPil == 1 && isRed == 0  )
  {
    redcapped();
  }
  else if ( pilot2 == 1 && currPil == 2 && isBlue == 0  )
  {
    bluecapped();
  }
  else if ( pilot2 == 2 && currPil == 2 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot3 == 1 && currPil == 3 && isBlue == 0  )
  {
    bluecapped();
  }
  else if ( pilot3 == 2 && currPil == 3 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot4 == 1 && currPil == 4 && isBlue == 0 )
  {
    bluecapped();
  }
  else if ( pilot4 == 2 && currPil == 4 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot5 == 1 && currPil == 5 && isBlue == 0 )
  {
    bluecapped();
  }
  else if ( pilot5 == 2 && currPil == 5 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot6 == 1 && currPil == 6 && isBlue == 0  )
  {

    bluecapped();
  }
  else if ( pilot6 == 2 && currPil == 6 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot7 == 1 && currPil == 7 && isBlue == 0  )
  {
    bluecapped();
  }
  else if ( pilot7 == 2 && currPil == 7 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot8 == 1 && currPil == 8 && isBlue == 0  )
  {
    bluecapped();
  }
  else if ( pilot8 == 2 && currPil == 8 && isRed == 0  )
  {
    redcapped();
  }
}




