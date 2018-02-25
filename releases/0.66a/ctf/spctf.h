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

void ledsCapture()
{
  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  if (capStatus + startfromLed == internalLeds + externalLeds - 1)
  {
    playLapTones();

    for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Blue;
      FastLED.show();
      spCaptured = 2;
    }

  }
  else if (capStatus + startfromLed < internalLeds + externalLeds && spCaptured < 3 )
  {
    leds[capStatus + startfromLed] = CRGB::Blue;
    FastLED.show();
    capStatus++;
    delay(1000);
    spCaptured = 1;
  }
}

int ledsBlack()
{
  if ( haveexternalleds == true ) {
    startfromLed = internalLeds;
  }
  if (capStatus + startfromLed > startfromLed && spCaptured > 0 )
  {
    leds[capStatus + startfromLed] = CRGB::Black;
    FastLED.show();
    capStatus--;
    delay(1000);
    isBlue = 0;

    // Serial.println(gameStarted);
  }
  else if (capStatus + startfromLed == startfromLed && spCaptured > 0)
  {
    clearLeds();
    spCaptured = 3;
  }


}

int spctf()
{
  if (channelIndex == 0)
  {
    playLapTones(); // (CC) does a beep
    ledsCapture();
  }
}

int runspTimer()
{
  if (spTimer < spdifficulty ) // (CC) running a int loop 10x to give some time to the receiver to pickup any RSSI's. I found if I didn't do this it would change the channel to quickly and not find any RSSI. If you know any other way that this would work let me know :)
  {
    spTimer++;
  }
  if (spTimer >= spdifficulty)  //(CC) once runloop gets to 10 it will go up one channel and reset the runloop to 0 (in order to change to the next channel and so on)
  {
    ledsBlack();
    spTimer = 0;
  }
}



