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

void checkBlueRed()
{
  if ( gameStarted == 0 )
  {
    bigMessage = "";
    smallMessage1 = "";
    smallMessage2 = "";
    gameStarted++;
  }
  else if ( gameStarted == 1 )
  {
    SetTimer(0, timerMin, timerSec); // Game timer
    bigMessage = "";
    StartTimer();
    gameStarted++;
  }
  if ( pilot1 == 1 && channelIndex == 0 && isBlue == 0 )
  {
    bluecapped();
  }
  else if ( pilot1 == 2 && channelIndex == 0 && isRed == 0  )
  {
    redcapped();
  }
  else if ( pilot2 == 1 && channelIndex == 1 && isBlue == 0  )
  {

    bluecapped();
  }
  else if ( pilot2 == 2 && channelIndex == 1 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot3 == 1 && channelIndex == 2 && isBlue == 0  )
  {
    bluecapped();
  }
  else if ( pilot3 == 2 && channelIndex == 2 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot4 == 1 && channelIndex == 3 && isBlue == 0 )
  {
    bluecapped();
  }
  else if ( pilot4 == 2 && channelIndex == 3 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot5 == 1 && channelIndex == 4 && isBlue == 0 )
  {

    bluecapped();
  }
  else if ( pilot5 == 2 && channelIndex == 4 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot6 == 1 && channelIndex == 5 && isBlue == 0  )
  {

    bluecapped();
  }
  else if ( pilot6 == 2 && channelIndex == 5 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot7 == 1 && channelIndex == 6 && isBlue == 0  )
  {

    bluecapped();
  }
  else if ( pilot7 == 2 && channelIndex == 6 && isRed == 0  )
  {
    redcapped();
  }
  if ( pilot8 == 1 && channelIndex == 7 && isBlue == 0  )
  {

    bluecapped();
  }
  else if ( pilot8 == 2 && channelIndex == 7 && isRed == 0  )
  {
    redcapped();
  }
}

void dctf()
{
  if (channelIndex == 0) // (CC) BLUE TEAM STARTS HERE (CC) checks to see if your drone is in channel 1
  {
    playLapTones();
    runloop = 0;  // (CC) sets runloop to 0 to start changing frequencies
    checkBlueRed(); // (CC) changes the flag to be marked as captured for team BLUE or team RED
  }
  else if (channelIndex == 1) //  (CC) checks to see if your drone is in channel 2
  {
    playLapTones();
    runloop = 0;
    checkBlueRed();
  }

  else  if (channelIndex == 2)  //  (CC) checks to see if your drone is in channel 3
  {

    playLapTones();
    runloop = 0;
    checkBlueRed();

  }
  else if (channelIndex == 3)  //  (CC) checks to see if your drone is in channel 4
  {
    playLapTones();
    runloop = 0;
    checkBlueRed();
  }
  else if (channelIndex == 4)   // (CC) RED TEAM START HERE // (CC) checks to see if your drone is in channel 5
  {
    playLapTones();
    runloop = 0;
    checkBlueRed();
  }
  else if (channelIndex == 5)  //  (CC) checks to see if your drone is in channel 6
  {
    playLapTones();
    runloop = 0;
    checkBlueRed();
  }
  else if (channelIndex == 6)  //  (CC) checks to see if your drone is in channel 7
  {
    playLapTones();
    runloop = 0;
    checkBlueRed();

  }
  else if (channelIndex == 7)  //  (CC) checks to see if your drone is in channel 8
  {
    playLapTones();
    runloop = 0;
    checkBlueRed();
  }
}
