int ledsCapture()
{
  if (capStatus == NUM_LEDS - 1)
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Blue;
      FastLED.show();
    }
  }
  else if (capStatus < NUM_LEDS && spCaptured < 2 )
  {
    leds[capStatus] = CRGB::Blue;
    FastLED.show();
    capStatus++;
    delay(1000);
    spCaptured = 1;
    Serial.print(capStatus);
  }


}

int ledsBlack()
{
  if (capStatus > 0 && spCaptured > 0 )
  {
    leds[capStatus] = CRGB::Black;
    FastLED.show();
    capStatus--;
    delay(1000);
  }
  else if (capStatus == 0 && spCaptured > 0)
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Black;
      FastLED.show();
    }
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



