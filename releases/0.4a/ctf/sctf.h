int sctf()
{
  if (channelIndex == 0) // (CC) BLUE TEAM STARTS HERE (CC) checks to see if your drone is in channel 1
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      playLapTones(); // (CC) does a beep
      checkBlueRedsimple();
    }

  }
  else if (channelIndex == 1) //  (CC) checks to see if your drone is in channel 2
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      playLapTones(); // (CC) does a beep
      checkBlueRedsimple();
    }
  }

  else  if (channelIndex == 2)  //  (CC) checks to see if your drone is in channel 3
  {
    for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {

      playLapTones(); // (CC) does a beep
      checkBlueRedsimple();

    }

  }
  else if (channelIndex == 3)  //  (CC) checks to see if your drone is in channel 4
  {

    playLapTones(); // (CC) does a beep
    checkBlueRedsimple();

  }
  else if (channelIndex == 4)   // (CC) RED TEAM START HERE // (CC) checks to see if your drone is in channel 5
  {

    playLapTones(); // (CC) does a beep
    checkBlueRedsimple();

  }
  else if (channelIndex == 5)  //  (CC) checks to see if your drone is in channel 6
  {

    playLapTones(); // (CC) does a beep
    checkBlueRedsimple();

  }
  else if (channelIndex == 6)  //  (CC) checks to see if your drone is in channel 7
  {

    playLapTones(); // (CC) does a beep
    checkBlueRedsimple();

  }
  else if (channelIndex == 7)  //  (CC) checks to see if your drone is in channel 8
  {

    playLapTones(); // (CC) does a beep
    checkBlueRedsimple();

  }
}

