int confirmBlue()
{
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Black;
    FastLED.show();
  }
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Blue;
    FastLED.show();
    delay(100);
  }
}

int confirmRed()
{
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Black;
    FastLED.show();
  }
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Green;
    FastLED.show();
    delay(100);
  }
}

int ledsBlue()
{
  leds[capStatusBlue] = CRGB::Blue;
  FastLED.show();
  capStatusBlue++;
  delay(1000);
  // leds[capStatus] = CRGB::Black;
}

int ledsBluesimple()
{
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Blue;
    FastLED.show();
    delay(500);
  }
}

int ledsRed()
{
  leds[capStatusRed] = CRGB::Green;
  FastLED.show();
  capStatusRed++;
  delay(1000);
  //  leds[capStatusRed] = CRGB::Black;
}

int ledsRedsimple()
{
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Green;
    FastLED.show();
    delay(500);
  }
}



int checkBlueRed()
{
  if ( pilot1 == 'blue' && channelIndex == 0 && isBlue == 0 )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot1 == 'red' && channelIndex == 0 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
  else if ( pilot2 == 'blue' && channelIndex == 1 && isBlue == 0  )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot2 == 'red' && channelIndex == 1 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
  if ( pilot3 == 'blue' && channelIndex == 2 && isBlue == 0  )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot3 == 'red' && channelIndex == 2 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
  if ( pilot4 == 'blue' && channelIndex == 3 && isBlue == 0 )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot4 == 'red' && channelIndex == 3 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
  if ( pilot5 == 'blue' && channelIndex == 4 && isBlue == 0 )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot5 == 'red' && channelIndex == 4 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
  if ( pilot6 == 'blue' && channelIndex == 5 && isBlue == 0  )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot6 == 'red' && channelIndex == 5 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
  if ( pilot7 == 'blue' && channelIndex == 6 && isBlue == 0  )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot7 == 'red' && channelIndex == 6 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
  if ( pilot8 == 'blue' && channelIndex == 7 && isBlue == 0  )
  {
    if (capStatusBlue < NUM_LEDS )
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
  else if ( pilot8 == 'red' && channelIndex == 7 && isRed == 0  )
  {
    if (capStatusRed < NUM_LEDS )
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
}

int checkBlueRedsimple()
{
  if ( pilot1 == 'blue' && isBlue == 0 && channelIndex == 0 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot1 == 'red' && isRed == 0 && channelIndex == 0 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot2 == 'blue' && isBlue == 0 && channelIndex == 1 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot2 == 'red' && isRed == 0 && channelIndex == 1 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot3 == 'blue' && isBlue == 0 && channelIndex == 2 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot3 == 'red' && isRed == 0 && channelIndex == 2 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot4 == 'blue' && isBlue == 0 && channelIndex == 3 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot4 == 'red' && isRed == 0 && channelIndex == 3 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot5 == 'blue' && isBlue == 0 && channelIndex == 4 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot5 == 'red' && isRed == 0 && channelIndex == 4 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot6 == 'blue' && isBlue == 0 && channelIndex == 5 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot6 == 'red' && isRed == 0 && channelIndex == 5 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot7 == 'blue' && isBlue == 0 && channelIndex == 6 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot7 == 'red' && isRed == 0 && channelIndex == 6 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
  else if ( pilot8 == 'blue' && isBlue == 0 && channelIndex == 7 )
  {
    ledsBluesimple();
    isRed = 0;
    isBlue = 1;
  }
  else if ( pilot8 == 'red' && isRed == 0 && channelIndex == 7 )
  {
    ledsRedsimple();
    isRed = 1;
    isBlue = 0;
  }
}

