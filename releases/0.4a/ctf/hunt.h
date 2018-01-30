int hunt()
{
  if (channelIndex == 0 && capStatusBlue == 0 ) // (CC) checks to see if your drone is in channel 1
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      playLapTones(); // (CC) does a beep
      leds[whiteLed] = CRGB::Blue;  // (CC) changes leds to BLUE
      FastLED.show();
      delay(1000);   // (CC) takes 1 second to change leds. You can make this faster or slower if you want
      runloop = 0;  // (CC) sets runloop to 0 to start changing frequencies
    }
    capStatusBlue = 1;

  }
  else if (channelIndex == 1 && capStatusBlue == 0 ) //  (CC) checks to see if your drone is in channel 2
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      playLapTones();
      leds[whiteLed] = CRGB::Red;
      FastLED.show();
      delay(1000);
      runloop = 0;
    }
    capStatusBlue = 1;
  }

  else  if (channelIndex == 2 && capStatusBlue == 0 )  //  (CC) checks to see if your drone is in channel 3
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Yellow;
      FastLED.show();
      delay(1000);
      runloop = 0;
    }
    capStatusBlue = 1;

  }
  else if (channelIndex == 3 && capStatusBlue == 0 )  //  (CC) checks to see if your drone is in channel 4
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Green;
      FastLED.show();
      delay(1000);
      runloop = 0;

    }
    capStatusBlue = 1;
  }
  else if (channelIndex == 4 && capStatusBlue == 0 )   // (CC) RED TEAM START HERE // (CC) checks to see if your drone is in channel 5
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Purple;
      FastLED.show();
      delay(1000);
      runloop = 0;


    }
    capStatusBlue = 1;
  }
  else if (channelIndex == 5 && capStatusBlue == 0 )  //  (CC) checks to see if your drone is in channel 6
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Cyan;
      FastLED.show();
      delay(1000);
      runloop = 0;

    }
    capStatusBlue = 1;
  }
  else if (channelIndex == 6 && capStatusBlue == 0 )  //  (CC) checks to see if your drone is in channel 7
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds[whiteLed] = CRGB::Gray;
      FastLED.show();
      delay(1000);
      runloop = 0;

    }
    capStatusBlue = 1;
  }
  else if (channelIndex == 7 && capStatusBlue == 0 )  //  (CC) checks to see if your drone is in channel 8
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
    capStatusBlue = 1;

  }
}

