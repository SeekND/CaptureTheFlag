
void LEDnumber()
{
  bigMessage = "EXT LEDS";
  smallMessage1 =  externalLeds;
  smallMessage2 = ""; // r/l
}

/*int LEDbrightness()
  {
  bigMessage = String("BRIGHTNESS");
  smallMessage1 =  BRIGHTNESS;
  smallMessage2 = String("R to >   L to <");
  }*/

void modeShow()
{
  if  ( mode == 2 )
  {
    smallMessage1 =  "CTF ";
  }
  else if  ( mode == 3 )
  {
    smallMessage1 =  "DOM CTF";
  }
  else if  ( mode == 4 )
  {
    smallMessage1 =  "SP CTF";
  }
  else if  ( mode == 5 )
  {
    smallMessage1 =  "DM";
  }
  /*else if  ( mode == 6 )
    {
    // smallMessage1 =  String("Scavenger Hunt");
    }*/
}

void MODEset()
{

  bigMessage = "MODE";
  //if ( mode == 1 )
  //{
  //  smallMessage1 =  String("Original CTF");
  //}
  modeShow();
  smallMessage2 = "";
}

void RSSImenumanual()
{
  bigMessage = "RSSI";
  smallMessage1 = rssiThreshold;
  smallMessage2 = "" ;
}


void singleCTF()
{
  bigMessage = "LEVEL";
  smallMessage1 = spLevel;
  smallMessage2 = String(""); // r/l
}


void RSSImenu1()
{
  bigMessage = "RSSI";
  smallMessage1 = rssiThreshold;
  smallMessage2 = "Def";

  setupSys = 11;
}


void RSSImenu2()
{
  bigMessage = "RSSI";
  smallMessage1 = rssiThreshold;
  smallMessage2 = "Manual";
  setupSys = 12;
}

void RSSImenu3()   // 11 - 12 - 13
{
  channelIndex = 0;
  frequency = setModuleChannel(channelIndex, bandIndex);
  rssiChecker = getFilteredRSSI();
  bigMessage = "RSSI";
  smallMessage1 = "Press R";
  smallMessage2 = String(rssiChecker);
  setupSys = 13;
}

void PILOTSset()
{

  bigMessage = String("PILOTS");
  smallMessage1 =  numberPilots;
  smallMessage2 = String(""); // r/l
}
/*
  void    PILOTSfreq()
  {
  bigMessage = String("FREQS");
  smallMessage1 =  String("na");
  smallMessage2 = String("");
  }
*/

void PILOTScolorDM()
{
  smallMessage1 = String("");
  clearLeds();
  whiteLed = 0;
  colourBlue();
  whiteLed = 1;
  colourRed();
  whiteLed = 2;
  colourYellow();
  whiteLed = 3;
  colourGreen();
  whiteLed = 4;
  colourPurple();
  whiteLed = 5;
  colourCyan();
  whiteLed = 6;
  colourWhite();
  whiteLed = 7;
  colourBlue();
  delay(1000);
  colourRed();
  delay(1000);
  colourYellow();
  delay(1000);
  colourGreen();
  delay(1000);
  leds[whiteLed] = CRGB::Black;
  FastLED.show();
  whiteLed = 0;
}
void   PILOTScolor()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P1") + String("-R") + String(freqpilot1);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}
void   PILOTScolor2()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P2") + String("-R") + String(freqpilot2);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}
void   PILOTScolor3()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P3") + String("-R") + String(freqpilot3);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}

void   PILOTScolor4()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P4") + String("-R") + String(freqpilot4);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}

void   PILOTScolor5()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P5") + String("-R") + String(freqpilot5);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}

void   PILOTScolor6()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P6") + String("-R") + String(freqpilot6);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}


void   PILOTScolor7()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P7") + String("-R") + String(freqpilot7);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}

void   PILOTScolor8()
{
  bigMessage = String("COLORS");
  smallMessage1 =  String("P8") + String("-R") + String(freqpilot8);
  smallMessage2 = String(pickcolour);
  pickcolour = String("");
}

void  NUMBERleds()
{
  bigMessage = String("EXT LEDS");
  smallMessage1 = externalLeds;
  smallMessage2 = String(""); // r/l
}


void gameTimer()
{
  bigMessage = String("TIMER");
  smallMessage1 = String(timerMin) + ":" + String(timerSec);
  smallMessage2 = String("");
}

int  read_LCD_buttons()

{
  // Serial.println("reading buttons");
  int buttonValue = digitalRead(9);
  if (buttonValue == LOW) {
    return btnUP;
  }



  int buttonValue2 = digitalRead(6);

  if (buttonValue2 == LOW) {
    return btnDOWN;
  }



  int buttonValue3 = digitalRead(4);

  if (buttonValue3 == LOW) {
    return btnSELECT;
  }

  int buttonValue4 = digitalRead(3);

  if (buttonValue4 == LOW) {
    return btnLEFT;
  }


  int buttonValue5 = digitalRead(2);

  if (buttonValue5 == LOW) {
    return btnRIGHT;
  }



  return btnNONE;  // when all others fail, return this...


}


void buttonRight()
{
  if (setupSys == 0)
  {
    configured = 0;
  }
  else if ( setupSys == 11 )
  {

  }
  else if (setupSys == 13)
  {
    rssiChecker = getFilteredRSSI();
    bigMessage = String("RSSI");
    smallMessage1 = String("Put TX in R1");
    smallMessage2 = String(rssiChecker);
  }
  else  if ( setupSys == 14 )
  {
    rssiThreshold++;
    rssiThreshold++;
    rssiThreshold++;
    rssiThreshold++;
    rssiThreshold++;

    RSSImenumanual();
  }
  else if  ( setupSys == 21 )
  {

    if (mode < 5)
    {
      mode++;
      MODEset();
    }
  }
  else if  ( setupSys == 31 )
  {
    if (numberPilots < 8)
    {
      numberPilots++;
      PILOTSset();
    }
  }
  // else if  ( setupSys == 41 )
  // {
  //   //freqs
  // }
  else if  ( setupSys == 51 )
  {
    if ( mode == 4 )
    {
      if ( spLevel < 6 )
      {
        spLevel++;
        spdifficultysetting();
        singleCTF();
      }
    }
    else if ( mode == 5 )
    {
      // do nothing, it will just show pilots colours
    }
    else
    {
      pilot1 = 1;
      pickcolour = String("blue");
      PILOTScolor();
    }
  }
  else if  ( setupSys == 52 )
  {
    pilot2 = 1;
    pickcolour = String("blue");
    PILOTScolor2();
  }
  else if  ( setupSys == 53 )
  {
    pilot3 = 1;
    pickcolour = String("blue");
    PILOTScolor3();

  }
  else if  ( setupSys == 54 )
  {
    pilot4 = 1;
    pickcolour = String("blue");
    PILOTScolor4();
  }
  else if  ( setupSys == 55 )
  {
    pilot5 = 1;
    pickcolour = String("blue");
    PILOTScolor5();
  }
  else if  ( setupSys == 56 )
  {
    pilot6 = 1;
    pickcolour = String("blue");
    PILOTScolor6();
  }
  else if  ( setupSys == 57 )
  {
    pilot7 = 1;
    pickcolour = String("blue");
    PILOTScolor7();
  }

  else if  ( setupSys == 58 )
  {
    pilot8 = 1;
    pickcolour = String("blue");
    PILOTScolor8();
  }
  else if  ( setupSys == 61 )
  {
    if (externalLeds < 10)
    {
      externalLeds++;
      haveexternalleds = true;
      LEDnumber();
    }
  }

  else if  ( setupSys == 62 )
  {
    /* if ( brightnessSetting < 60 )
      {
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
        brightnessSetting++;
      FastLED.setBrightness(  brightnessSetting );
      }*/
  }

  else if  ( setupSys == 71 )
  {
    if (timerMin < 59 )
    {
      timerMin++;
      SetTimer(0, timerMin, timerSec);
      gameTimer();
    }
  }

}


void buttonLeft()
{
  // Serial.write("Left");
  if (setupSys == 0)
  {
    configured = 1;
  }
  else if ( setupSys == 14 ) // RSSI set manually
  {
    rssiThreshold--;
    rssiThreshold--;
    rssiThreshold--;
    rssiThreshold--;
    rssiThreshold--;
    RSSImenumanual();
  }
  else if ( setupSys == 15 ) // RSSI set automatically
  {
  }
  else if ( setupSys == 21 ) // MODE set
  {

    if (mode > 2)
    {
      mode--;
      MODEset();
    }
  }
  else if  ( setupSys == 31 )
  {

    if (numberPilots > 1)
    {
      numberPilots--;
      PILOTSset();
    }
  }
  //else if  ( setupSys == 41 )
  //{
  // freqs
  //}

  else if  ( setupSys == 51 )
  {

    if ( mode == 4 )
    {
      if ( spLevel > 1 )
      {
        spLevel--;
        spdifficultysetting();
        singleCTF();
      }
    }
    else if ( mode == 5 )
    {
      // do nothing, it will just show pilots colours
    }
    else
    {
      pilot1 = 2;
      pickcolour = String("red");
      PILOTScolor();
    }
  }
  else if  ( setupSys == 52 )
  {
    pilot2 = 2;
    pickcolour = String("red");
    PILOTScolor2();
  }
  else if  ( setupSys == 53 )
  {
    pilot3 = 2;
    pickcolour = String("red");
    PILOTScolor3();

  }
  else if  ( setupSys == 54 )
  {
    pilot4 = 2;
    pickcolour = String("red");
    PILOTScolor4();
  }
  else if  ( setupSys == 55 )
  {
    pilot5 = 2;
    pickcolour = String("red");
    PILOTScolor5();
  }
  else if  ( setupSys == 56 )
  {
    pilot6 = 2;
    pickcolour = String("red");
    PILOTScolor6();
  }
  else if  ( setupSys == 57 )
  {
    pilot7 = 2;
    pickcolour = String("red");
    PILOTScolor7();
  }

  else if  ( setupSys == 58 )
  {
    pilot8 = 2;
    pickcolour = String("red");
    PILOTScolor8();
  }

  else if  ( setupSys == 61 )
  {
    if (externalLeds > 0 )
    {
      externalLeds--;
      if (externalLeds == 0)
      {
        haveexternalleds = false;
        startfromLed = 0;
      }
      LEDnumber();
    }
  }

  else if  ( setupSys == 62 )
  {
    /* if ( brightnessSetting >10 )
        {
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
           brightnessSetting--;
       FastLED.setBrightness(  brightnessSetting );
        }*/
  }

  else if  ( setupSys == 71 )
  {

    if (timerMin > 1 )
    {
      timerMin--;
      SetTimer(0, timerMin, timerSec);
    }
    gameTimer();
  }
}

void buttonUp()
{
  //Serial.write("Up");

  if (setupSys == 12) // moves from RSSI (leave it) to RSSI manual
  {
    RSSImenu1();
  }

  else if (setupSys == 13) //  // moves from RSSI manual to RSSI auto
  {
    RSSImenu2();
  }
  else if  ( setupSys == 52 )
  {
    PILOTScolor();
    setupSys = 51;

  }
  else if  ( setupSys == 53 )
  {

    PILOTScolor2();
    setupSys = 52;
  }
  else if  ( setupSys == 54 )
  {

    PILOTScolor3();
    setupSys = 53;
  }
  else if  ( setupSys == 55 )
  {

    PILOTScolor4();
    setupSys = 54;
  }
  else if  ( setupSys == 56 )
  {

    PILOTScolor5();
    setupSys = 55;
  }
  else if  ( setupSys == 57 )
  {

    PILOTScolor6();
    setupSys = 56;
  }

  else if  ( setupSys == 58 )
  {

    PILOTScolor7();
    setupSys = 57;
  }
  else if (setupSys == 62 ) // moves to NUMBERLEDS
  {
    NUMBERleds();
    setupSys = 61;
  }
  else if (setupSys == 71)
  {
    if (timerSec == 30 )
    {
      timerSec = 0;
      SetTimer(0, timerMin, timerSec);
    }
    else if (timerSec == 0 )
    {
      timerSec = 30;
      SetTimer(0, timerMin, timerSec);
    }
    gameTimer();
  }
  else if  (setupSys == 99)
  {

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  }
}

void buttonDown()
{

  if (setupSys == 11) // moves from RSSI autp to RSSI manual
  {
    RSSImenu2();
  }
  else if (setupSys == 12) // moves from RSSI autp to RSSI (leave it)
  {
    RSSImenu3();
  }
  else if (setupSys == 14) // RSSI
  {
    RSSImenumanual();
  }
  else if  ( setupSys == 51 &&  1 < numberPilots && mode != 4 && mode != 5 )
  {
    PILOTScolor2();
    setupSys = 52;
  }
  else if  ( setupSys == 52 &&  2 < numberPilots )
  {

    PILOTScolor3();
    setupSys = 53;
  }
  else if  ( setupSys == 53 &&  3 < numberPilots )
  {

    PILOTScolor4();
    setupSys = 54;
  }
  else if  ( setupSys == 54 &&  4 < numberPilots )
  {

    PILOTScolor5();
    setupSys = 55;
  }
  else if  ( setupSys == 55 &&  5 < numberPilots )
  {

    PILOTScolor6();
    setupSys = 56;
  }
  else if  ( setupSys == 56 &&  6 < numberPilots )
  {

    PILOTScolor7();
    setupSys = 57;
  }
  else if  ( setupSys == 57 &&  7 < numberPilots )
  {

    PILOTScolor8();
    setupSys = 58;
  }
  else if  ( setupSys == 71 )
  {
    if (timerSec == 30 )
    {
      timerSec = 0;
      SetTimer(0, timerMin, timerSec);
    }
    else if (timerSec == 0 )
    {
      timerSec = 30;
      SetTimer(0, timerMin, timerSec);
    }
    gameTimer();
  }

}

void buttonSel()
{

  if (configured == 2)
  {
    configured = 0;
    gameReset();
  }
  if (setupSys == 0)
  {
    if ( configured == 1)
    {
      configured = 2;

      smallMessage1 = "";
      smallMessage2 = "";
      setupSys = 99;
    }
    else if ( configured == 0)  // moves to next menu >> RSSI
    {
      RSSImenu1();
      configured = 3;
      setupSys = 11 ; // test - remove if it doesn't work
    }

  }
  else if (setupSys == 11)  // moves to next menu >> MODE
  {

    MODEset();
    setupSys = 21;
    // goto next screen - no saves needed

  }
  else if (setupSys == 12)  // moves to RSSI manual
  {
    RSSImenumanual();
    setupSys = 14;
  }
  else if (setupSys == 13)  // moves to RSSI auto
  {
    rssiThreshold = rssiChecker;
    bigMessage = String("RSSI");
    smallMessage1 = String("RSSI saved");
    smallMessage2 = String(rssiThreshold);
    setupSys = 16;
  }
  else if (setupSys == 14) // moves to MODES
  {
    MODEset();
    setupSys = 21;
  }
  else if (setupSys == 16)  // moves to RSSI auto
  {
    MODEset();
    setupSys = 21;
  }
  else if (setupSys == 21)  // moves to PILOTS
  {
    if ( mode == 4 )
    {
      singleCTF();
      setupSys = 51;
    }
    else
    {
      PILOTSset();
      setupSys = 31;
    }
  }
  else if (setupSys == 31) // moves to PILOTSFREQ
  {
    //PILOTSfreq();
    //setupSys = 41;
    if ( mode == 4 )
    {
      singleCTF();
      setupSys = 51;
    }
    else if ( mode == 5 )
    {
      PILOTScolorDM();
      setupSys = 51;
    }
    else
    {
      PILOTScolor();
      setupSys = 51;
    }
  }
  /*else if (setupSys > 40 && setupSys < 49) // moves to PILOTCOLOR
    {
    if ( mode == 4 )
    {
      singleCTF();
      setupSys = 51;
    }
    else
    {
      PILOTScolor();
      setupSys = 51;
    }
    }*/
  else if (setupSys > 50 && setupSys < 59 ) // moves to NUMBERLEDS
  {
    clearLeds();
    NUMBERleds();
    setupSys = 61;
  }
  else if (setupSys > 60 && setupSys < 63 ) // moves to GAMETIMER
  {
    gameTimer();
    setupSys = 71;
  }
  else if (setupSys == 71) // moves to GAMETIMER
  {

    smallMessage1 = "";
    smallMessage2 = "";
    setupSys = 99;
    configured = 2;
    //RESETALLPREFCONFIGS();
  }
}





boolean TimeHasChanged()
{
  return timeFlag;
}

// output true if timer equals requested time
boolean TimeCheck(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
  return ( minutes == ShowMinutes() && seconds == ShowSeconds());
}



void autoConfig()
{
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {

    case btnRIGHT:

      {
        buttonRight();
        delay(500);
        break;

      }

    case btnLEFT:

      {
        buttonLeft();
        delay(500);
        break;

      }

    case btnDOWN:

      {
        buttonDown();
        delay(500);
        break;

      }

    case btnUP:
      {
        buttonUp();

        delay(500);
        break;
      }




    case btnSELECT:

      {
        buttonSel();

        delay(500);
        break;

      }

  }
}
