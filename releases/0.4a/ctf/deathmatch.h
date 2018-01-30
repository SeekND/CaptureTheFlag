int dm()
{
  if (channelIndex == 0) // (CC) checks to see if your drone is in channel 1
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      playLapTones(); // (CC) does a beep
      leds[whiteLed] = CRGB::Blue;  // (CC) changes leds to BLUE
      FastLED.show();
      delay(1000);   // (CC) takes 1 second to change leds. You can make this faster or slower if you want
      runloop = 0;  // (CC) sets runloop to 0 to start changing frequencies

      channelIndex = 1; // (CC) changes to the next frequency so it doesn't loop the recapture
      frequency = setModuleChannel(channelIndex, bandIndex);   // (CC) this is what changes the frequency. The band stays the same.

    }

  }
  else if (channelIndex == 1) //  (CC) checks to see if your drone is in channel 2
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      playLapTones();
      leds[whiteLed] = CRGB::Red;
      FastLED.show();
      delay(1000);
      runloop = 0;

      channelIndex = 2;
      frequency = setModuleChannel(channelIndex, bandIndex);

    }
  }

  else  if (channelIndex == 2)  //  (CC) checks to see if your drone is in channel 3
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Yellow;
      FastLED.show();
      delay(1000);
      runloop = 0;

      channelIndex = 3;
      frequency = setModuleChannel(channelIndex, bandIndex);
    }

  }
  else if (channelIndex == 3)  //  (CC) checks to see if your drone is in channel 4
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Green;
      FastLED.show();
      delay(1000);

      runloop = 0;
      channelIndex = 4;
      frequency = setModuleChannel(channelIndex, bandIndex);

    }
  }
  else if (channelIndex == 4)   // (CC) RED TEAM START HERE // (CC) checks to see if your drone is in channel 5
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Purple;
      FastLED.show();
      delay(1000);
      runloop = 0;
      channelIndex = 5;
      frequency = setModuleChannel(channelIndex, bandIndex);    // (CC) this is the code to set the frequency. The band never changes, only the channel, marked above.


    }
  }
  else if (channelIndex == 5)  //  (CC) checks to see if your drone is in channel 6
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Cyan;
      FastLED.show();
      delay(1000);
      runloop = 0;
      channelIndex = 6;
      frequency = setModuleChannel(channelIndex, bandIndex);

    }
  }
  else if (channelIndex == 6)  //  (CC) checks to see if your drone is in channel 7
  {


    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed +  1 )
    {

      FastLED.delay(33);
      leds[whiteLed] = CRGB::Gray;
      FastLED.show();
      delay(1000);
      runloop = 0;
      channelIndex = 7;
      frequency = setModuleChannel(channelIndex, bandIndex);



    }
  }
  else if (channelIndex == 7)  //  (CC) checks to see if your drone is in channel 8
  {
    leds[0] = CRGB::Blue; // need to find another colour
    FastLED.show();
    delay(1000);
    leds[1] = CRGB::Red; // need to find another colour
    FastLED.show();
    delay(1000);
    leds[2] = CRGB::Green; // need to find another colour
    FastLED.show();
    delay(1000);
    leds[3] = CRGB::Yellow; // need to find another colour
    FastLED.show();
    delay(1000);

    runloop = 0;
    channelIndex = 0;
    frequency = setModuleChannel(channelIndex, bandIndex);
  }
}

