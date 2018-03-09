/**
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



//  --------------------------  THINGS THE USER SHOULD SETUP  -----------------------
uint16_t rssiThreshold = 235 ; // (CC) play around with this value to find your best RSSI threshold. (between 190 to 260 seem to be acceptable values). The higher the value the closer the quad needs to get. But if it's too high it wont detect it.

// CTF colours 1 = blue , 2= red
byte pilot1 = 1;
byte pilot2 = 1;
byte pilot3 = 2;
byte pilot4 = 2;
byte pilot5 = 1;
byte pilot6 = 1;
byte pilot7 = 2;
byte pilot8 = 2;

// all colours for other - non team - game times 1 = blue , 2= red , 3= green, 4= yellow, 5= purple, 6= cyan, 7= white, 8= orange
byte pilot1o = 8;
byte pilot2o = 7;
byte pilot3o = 6;
byte pilot4o = 5;
byte pilot5o = 4;
byte pilot6o = 3;
byte pilot7o = 2;
byte pilot8o = 1;


byte numberPilots = 4;


// LEDS
uint32_t BRIGHTNESS =  10;
boolean haveexternalleds = false; // do you have external leds?? (array connected to the main arduino leds)
byte internalLeds = 8; // max 20 only with external voltage // max 10 with 5v from Arduino
byte externalLeds = 0;  // max 20 total with internal and external leds (eg: if you are using 10 internal leds you can use 10 max external


// GAMEMODE
byte mode = 2;    // set your prefered mode
//  mode 2:Simple CTF team game (only blue flag and red flag) - flags get captured as soon as your signal is detected. This is a super fast game for super fast people. Don't blink!
//  mode 3:Domination CTF
//  mode 4:Single Player CTF
//  mode 5:Free For All Deathmatch (each flag will turn to each colour of the pilot) P1 = BLUE , P2 = RED , P3 = YELLOW, P4= RED, P5 =CYAN, P6 =VIOLET,P7= WHITE, P8= ORANGE

// DIFICULTY (SP ONLY)
byte spLevel = 4;    // set the level of difficulty you want for the single player CTF only
// 1 = rookie
// 2 = easy
// 3 = medium
// 4 = hard
// 5 = hardcode
// 6 = insanel3

// GAME TIMER
byte timerMin = 2; // minutes
byte timerSec = 0; // seconds



//  --------------------------  END OF USER SETUP // DO NOT TOUCH VARIABLES BELOW  -----------------------



#include <SPI.h>
#include <Wire.h>
#include "FastLED.h"
#include <avr/pgmspace.h>


//----- CLOCK CONFIG --------------------------------------

#define NUM_LEDS 20
CRGB leds[NUM_LEDS];

unsigned long Watch, _micro, time = micros();
unsigned int Clock = 0, R_clock;
boolean Reset = false, Stop = false, Paused = false;
volatile boolean timeFlag = false;



//----- SOUND CONFIG --------------------------------------

const uint16_t musicNotes[] PROGMEM = { 523, 587, 659, 698, 784, 880, 988, 1046 };
// number of analog rssi reads to average for the current check.
// single analog read with FASTADC defined (see below) takes ~20us on 16MHz arduino
// so e.g. 10 reads will take 200 ms, which gives resolution of 5 RSSI reads per ms,
// this means that we can theoretically have 1ms timing accuracy :)
#define RSSI_READS 5 // 5 should give about 10 000 readings per second



//----- RSSI --------------------------------------

#define FILTER_ITERATIONS 5
uint16_t rssiArr[FILTER_ITERATIONS + 1];
uint16_t rssi;

#define RSSI_MAX 1024
#define RSSI_MIN 0
#define MAGIC_THRESHOLD_REDUCE_CONSTANT 2
#define THRESHOLD_ARRAY_SIZE  100
uint16_t rssiThresholdArray[THRESHOLD_ARRAY_SIZE];

#define DEFAULT_RSSI_MONITOR_DELAY_CYCLES 1000 //each 100ms, if cycle takes 100us
#define MIN_RSSI_MONITOR_DELAY_CYCLES 10 //each 1ms, if cycle takes 100us, to prevent loss of communication
uint16_t rssiMonitorDelayCycles = DEFAULT_RSSI_MONITOR_DELAY_CYCLES;



//----- TIMER SETUP --------------------------------------

void SetTimer(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
  // This handles invalid time overflow ie 1(H), 0(M), 120(S) -> 1, 2, 0
  unsigned int _S = (seconds / 60), _M = (minutes / 60);
  if (_S) minutes += _S;
  if (_M) hours += _M;

  Clock = (hours * 3600) + (minutes * 60) + (seconds % 60);
  R_clock = Clock;
  Stop = true;
}

void SetTimer(unsigned int seconds)
{
  // StartTimer(seconds / 3600, (seconds / 3600) / 60, seconds % 60);
  Clock = seconds;
  R_clock = Clock;
  Stop = true;
}


//-------GLOBALS ------------------------------------------
boolean setupRan = true;
uint8_t allowEdgeGeneration = 0;
uint8_t channelIndex = 0;
uint8_t bandIndex = 0;
uint8_t isSoundEnabled = 1;
uint8_t rssiMonitor = 1;
uint16_t rssiMonitorDelayExpiration = 0;
byte captured = 0;
byte capStatus = 0;
byte capStatusBlue = 0;
byte capStatusRed = 0;
uint16_t frequency = 0;
uint16_t runloop = 0;
uint16_t runloopsp = 0;
byte isBlue = 0;           // Flag is blue on 1
byte isRed = 0;            // Flag is red on 1
int pointsRed = 0;
int pointsBlue = 0;
byte spCaptured = 0;
int spTimer = 0;
int spdifficulty = 0;
byte setupSys = 0;
byte configured = 2;
String bigMessage = String("");
String smallMessage1 = String("");
String smallMessage2 = String("");
byte rssiChecker = 0;
byte gameStarted = 0;
byte startfromLed = 0;
byte gamesPlayed = 1;
byte ledsUp = 1;
byte currPil = 0;
byte chanP1 = 0;
byte bandP1 = 0;
byte chanP2 = 2;
byte bandP2 = 0;
byte chanP3 = 4;
byte bandP3 = 0;
byte chanP4 = 6;
byte bandP4 = 0;
byte chanP5 = 1;
byte bandP5 = 0;
byte chanP6 = 3;
byte bandP6 = 0;
byte chanP7 = 5;
byte bandP7 = 0;
byte chanP8 = 7;
byte bandP8 = 0;
boolean configureScreen = false;



// --------------INTERNAL FILES --------------------------------------------------------------

#include "fastReadWrite.h"
#include "fastADC.h"
#include "pinAssignments.h"
#include "channels.h"
#include "rx5808spi.h"
#include "sounds.h"
#include "leds.h"
#include "scoring.h"
#include "config.h"
#include "ibutton.h"

#include "sctf.h"
#include "dctf.h"
#include "spctf.h"
#include "deathmatch.h"


// ------------------------------------------------------------------------------------------


void setup() {

  Serial.begin(9600);

  delay(2000);

  pinMode(buzzerPin, OUTPUT); // init buzzer pin
  pinMode(buttonPin, INPUT_PULLUP); // 1 button config

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );

  spdifficultysetting(); // set difficulty for SPCTF


  // initialize digital pin 13 LED as an output.
  pinMode(led, OUTPUT);
  digitalHigh(led);

  // SPI pins for RX control
  setupSPIpins();

  channelIndex = chanP1;
  bandIndex = bandP1;
  frequency = setModuleChannel(channelIndex, bandIndex);

  initFastADC();

  if (haveexternalleds == false )  // just in case you put some extra leds but forgot to change the values
  {
    startfromLed = 0;
    externalLeds = 0;
  }
  else if ( haveexternalleds == true )
    startfromLed = internalLeds;


  SetTimer(0, timerMin, timerSec); // Game timer

  allowEdgeGeneration = 0;

  // Setup Done - Turn Status LED off.
  digitalLow(led);

  Serial.println("Finished setup");

}
// ----------------------------------------------------------------------------
void loop() {

  if ( setupSys == 41)
  {
    rssi = getFilteredRSSI();
    if (rssi > rssiThreshold)
    {
      colourRed(0);
    }
    else
    {
      colourWhite(0);
    }
  }


  lcd_1key = read_1_button();

  CountDownTimer(); // run the countdown timer


  if ( configured == 2 )
  {
    channelScan_allchannels(); // scans all channels
    rssi = getFilteredRSSI();  // assigns the rssi


    if ( gameStarted == 0 )
    {
      bigMessage = "WAITING";

      if (setupRan == true)
      {
        if ( haveexternalleds == true ) {
          startfromLed = internalLeds;
        }
        for (byte whiteLed = startfromLed; whiteLed < mode + startfromLed; whiteLed = whiteLed + 1)
        {
          colourWhite(whiteLed);
        }

        delay(2000);
        
        lightsReady();
        
        for (byte whiteLed = startfromLed; whiteLed < gamesPlayed + startfromLed; whiteLed = whiteLed + 1)
        {
          colourGreen(whiteLed);
          delay(100);
        }
        setupRan = false;
      }
    }

    
    if (isBlue == 1)
    {
      if ( mode == 4 && spCaptured < 2 )
      {
        // do nothing.
      }
      else if ( mode == 4 && spCaptured == 2 )
      {
        scoreBlue();
      }
      else
      {
        scoreBlue();
      }
    }
    if (isRed == 1)
    {
      scoreRed();
    }



    if ( gameStarted == 1 )
    {
      SetTimer(0, timerMin, timerSec); // Game timer
      bigMessage = "";
      StartTimer();
      gameStarted++;

      Serial.println("Game started");
    }



    if (rssiThreshold > 0) { // threshold = 0 means that we don't check rssi values
      if (rssi > rssiThreshold)
      { // rssi above the threshold - drone is near
        if (allowEdgeGeneration)
        { // we haven't fired event for this drone proximity case yet
          allowEdgeGeneration = 0;
          if ( gameStarted == 0 )
          {
            bigMessage = "";
            smallMessage1 = "";
            smallMessage2 = "";
            gameStarted++;
          }

          if ( mode == 2 )
          {
            sctf();
          }
          else if ( mode == 3 )
          {
            dctf();
          }
          else if ( mode == 4 )
          {
            spctf();
            isBlue = 1;
            scoreBlue();
            scoreBlue();
            scoreBlue();
            scoreBlue();
            scoreBlue();
            scoreBlue();
            scoreBlue();
            scoreBlue();
            scoreBlue();
            scoreBlue();
          }
          else if ( mode == 5 || mode == 6 )  // (CC) DEATHMATCH
          {
            deathmatch();
          }
        }
      }
      else
      {
        allowEdgeGeneration = 1; // we're below the threshold, be ready to catch another case
        if ( mode == 4 )
        {
          runspTimer();
        }
      }
    }
  }
  else if (configured == 0)
  {
    bigMessage = "MAIN";
    smallMessage1 = "Use def?";
    smallMessage2 = "n";
  }
  else if (configured == 1)
  {
    bigMessage = "MAIN";
    smallMessage1 = "Use def?";
    smallMessage2 = "y";
  }
}




