
int gameModes()
{

  if ( mode  == 1 )
  {
    mode = 1;
    digitalLow(led);
    delay (1000);
    digitalHigh(led);
    delay (1000);
    digitalLow(led);
    delay (1000);
  }
  else if (mode  == 2)
  {
    digitalLow(led);
    delay (1000);
    digitalHigh(led);
    delay (1000);
    digitalLow(led);
    delay (1000);
    digitalHigh(led);
    delay (1000);
    digitalLow(led);
    delay (1000);
  }
  else if (mode  == 3)
  {
    digitalLow(led);
    delay (1000);
    digitalHigh(led);
    delay (1000);
    digitalLow(led);
    delay (1000);
    digitalHigh(led);
    delay (1000);
    digitalLow(led);
    delay (1000);
    digitalHigh(led);
    delay (1000);
    digitalLow(led);
    delay (1000);
  }

}
