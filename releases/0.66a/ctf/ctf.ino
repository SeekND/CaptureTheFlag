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

/*********************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x32 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#include "FastLED.h"
#define DATA_PIN 5      // (CC) this is the data pin (D5) on your arduino where you connect the signal cable for the leds. This works only with leds that have 5v,Ground,Din (if you have one that has R,G,B connections it won't work.


unsigned long Watch, _micro, time = micros();
unsigned int Clock = 0, R_clock;
boolean Reset = false, Stop = false, Paused = false;
volatile boolean timeFlag = false;

boolean setupRan = true;



#define API_VERSION 2 // version number to be increased with each API change (int16)

// #define DEBUG

#ifdef DEBUG
#define DEBUG_CODE(x) do { x } while(0)
#else
#define DEBUG_CODE(x) do { } while(0)
#endif

uint8_t MODULE_ID = 0;
uint8_t MODULE_ID_HEX = '0';

#define SERIAL_DATA_DELIMITER '\n'

#include <avr/pgmspace.h>


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


//----- Timer -------------------------------
//unsigned long currentMillis = 0;
//int32_t timeCalibrationConst = 0;


//----- other globals------------------------------
uint8_t allowEdgeGeneration = 0;
uint8_t channelIndex = 0;     // (CC) This starts the module in channel 1 ( yes, 0 means channel 1, 1 means channel 2 ... 7 means channel 8 .. you get the picture ;)  )
uint8_t bandIndex = 0;        // (CC) This starts the module in Raceband. Check Channels.h file if you want to use another band instead.
uint8_t isSoundEnabled = 1;
uint8_t rssiMonitor = 1;
uint16_t rssiMonitorDelayExpiration = 0;
byte capStatus = 0;
byte capStatusBlue = 0;
byte capStatusRed = 0;
uint16_t frequency = 0;
uint16_t runloop = 0;          // (CC) because I couldn't find any other way to make the code wait after the frequency had been changed I have to run a numeric loop that runs from 0 to 10. At 10 it moves to the next frequency then resets to 0, and runs the loop again.
uint16_t runloopsp = 0;
byte isBlue = 0;           // Flag is blue
byte isRed = 0;            // Flag is red
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
byte whiteLed = 0;


//  --------------------------  THINGS THE USER SHOULD SETUP  -----------------------
boolean configureScreen = false;
uint16_t rssiThreshold = 215 ; // (CC) play around with this value to find your best RSSI threshold. (between 190 to 260 seem to be acceptable values). The higher the value the closer the quad needs to get. But if it's too high it wont detect it.

// 1 = blue , 2= red
byte pilot1 = 1;
byte pilot2 = 1;
byte pilot3 = 2;
byte pilot4 = 2;
byte pilot5 = 1;
byte pilot6 = 1;
byte pilot7 = 2;
byte pilot8 = 2;

// default band is Raceband
byte freqpilot1 = 1;
byte freqpilot2 = 3;
byte freqpilot3 = 5;
byte freqpilot4 = 7;
byte freqpilot5 = 2;
byte freqpilot6 = 4;
byte freqpilot7 = 6;
byte freqpilot8 = 8;

byte numberPilots = 4;


// LEDS
#define BRIGHTNESS  64  // (CC) how bright the leds are. 64 is max
#define NUM_LEDS 18  // enter total amount of leds (internal AND external)  DONT FORGET TO PUT THIS!!
byte internalLeds = 8; // enter total amount of internal leds - DONT FORGET TO PUT THIS!!
byte externalLeds = 0;  // enter total amount of external leds - this can be changed via screen configuration as well
boolean haveexternalleds = false; // do you have external leds?? false = no, true = yes   - this is auto configured if you are using a screen

// GAMEMODE
byte mode = 4;    // set your prefered mode
//  mode 2:Simple CTF team game (only blue flag and red flag) - flags get captured as soon as your signal is detected. This is a super fast game for super fast people. Don't blink!
//  mode 3:Domination CTF
//  mode 4:Single Player CTF
//  mode 5:Free For All Deathmatch (each flag will turn to each colour of the pilot) P1 = BLUE , P2 = RED , P3 = YELLOW, P4= RED, P5 =CYAN, P6 =VIOLET,P7= WHITE, P8= MULTICOLOUR
//  mode 6:Scavenger hunt (once you capture a flag it will stay in that colour, no one else can capture it) // NA atm

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
byte timerSec = 30; // seconds







// ---------------------TIMER SETUP --------------------------------

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

// ----------------------------------------------------------------------------
CRGB leds[NUM_LEDS];
#include "fastReadWrite.h"
#include "fastADC.h"
#include "pinAssignments.h"
#include "channels.h"
// #include "sendSerialHex.h"
#include "rx5808spi.h"
#include "sounds.h"
#include "leds.h"
#include "config.h"
#include "scoring.h"
#include "ibutton.h"
#include "buttons.h"

#include "modes.h"
#include "sctf.h"
#include "dctf.h"
#include "spctf.h"
#include "deathmatch.h"
//#include "hunt.h"

// ----------------------------------------------------------------------------




void setup() {

  Serial.begin(9600);

  // Serial.println("start");
  //Stop = true;

  //Serial.println("began setup");
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();

  delay(2000);



  // Clear the buffer.
  display.clearDisplay();

  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println("WELCOME");
  display.println("TO CTF");

  display.display();
  delay(2000);
  display.clearDisplay();

  pinMode(9, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);


  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  clearLeds(); // makes all leds black

  spdifficultysetting();
  // set difficulty for SPCTF

  // initialize digital pin 13 LED as an output.
  pinMode(led, OUTPUT);
  digitalHigh(led);

  // init buzzer pin
  pinMode(buzzerPin, OUTPUT);

  //init raspberrypi interrupt generator pin
  pinMode(pinRaspiInt, OUTPUT);
  digitalLow(pinRaspiInt);

  // SPI pins for RX control
  setupSPIpins();

  // set the channel as soon as we can
  // faster boot up times :)
  frequency = setModuleChannel(channelIndex, bandIndex);

  assignPilotfreqs();


  initFastADC();

  if (haveexternalleds == false )  // just in case you put some extra leds but forgot to change the values
  {

    startfromLed = 0;
    externalLeds = 0;
  }


  SetTimer(0, timerMin, timerSec); // Game timer
  //StartTimer();

  DEBUG_CODE(
    pinMode(serialTimerPin, OUTPUT);
    pinMode(loopTimerPin, OUTPUT);
    pinMode(bufferBusyPin, OUTPUT);
    pinMode(sequencePin, OUTPUT);
  );

  allowEdgeGeneration = 0;




  // Setup Done - Turn Status LED off.
  digitalLow(led);

  Serial.println("finished setup");

}
// ----------------------------------------------------------------------------
void loop() {
  DEBUG_CODE(
    digitalToggle(loopTimerPin);
  );

  if ( configureScreen == true )
  {
    lcd_key = read_LCD_buttons();  // checks if a button is being pressed
    autoConfig(); // checks what should be done when a button was pressed
  }
  else
  {
    lcd_1key = read_1_button();
    // auto1Config();
  }


  CountDownTimer(); // run the countdown timer


  if ( configured == 2 )
  {
    channelScan_allchannels(); // scans all channels
    rssi = getFilteredRSSI();  // assigns the rssi

    if (gameStarted == 1);
    {
      if (TimeHasChanged() )
      {
        bigMessage = String(ShowMinutes()) + ":" + String(ShowSeconds());
      }
    }
    if ( gameStarted == 0 )
    {
      bigMessage = "WAITING";
      modeShow();
      if (setupRan == true)
      {
        if ( haveexternalleds == true ) {
          startfromLed = internalLeds;
        }
        for (whiteLed = startfromLed; whiteLed < mode + startfromLed; whiteLed = whiteLed + 1)
        {
          leds[whiteLed] = CRGB::Red;
          FastLED.show();
          delay(50);
        }

        delay(2000);
        lightsReady();
        for (whiteLed = startfromLed; whiteLed < gamesPlayed + startfromLed; whiteLed = whiteLed + 1)
        {
          leds[whiteLed] = CRGB::Red;
          FastLED.show();
          delay(100);
        }
        setupRan = false;
      }

    }
    if (isBlue == 1)
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
      if ( gameStarted == 0 )
      {

        bigMessage = "";
        gameStarted++;
      }
      else if ( gameStarted == 1 )
      {

        SetTimer(0, timerMin, timerSec); // Game timer
        StartTimer();
        gameStarted++;
      }
      scoreRed();
    }




    if (rssiThreshold > 0) { // threshold = 0 means that we don't check rssi values
      if (rssi > rssiThreshold)
      { // rssi above the threshold - drone is near
        if (allowEdgeGeneration)
        { // we haven't fired event for this drone proximity case yet
          allowEdgeGeneration = 0;
          gen_rising_edge(pinRaspiInt);  //generate interrupt for EasyRaceLapTimer software

          digitalLow(led);




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
          else if ( mode == 5 )  // (CC) DEATHMATCH
          {
            dm();
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

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.setTextColor(BLACK, WHITE);
  display.println(bigMessage);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println( smallMessage1 );
  display.println( smallMessage2 );
  display.display();
  display.clearDisplay();
}



// ----------------------------------------------------------------------------
uint16_t setRssiMonitorDelay(uint16_t delay) {
  return delay < MIN_RSSI_MONITOR_DELAY_CYCLES ? MIN_RSSI_MONITOR_DELAY_CYCLES : delay;
}
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------
uint16_t getMedian(uint16_t a[], uint16_t size) {
  return a[size / 2];
}
// ----------------------------------------------------------------------------
void gen_rising_edge(int pin) {
  digitalHigh(pin); //this will open mosfet and pull the RasPi pin to GND
  delayMicroseconds(10);
  digitalLow(pin); // this will close mosfet and pull the RasPi pin to 3v3 -> Rising Edge
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------


boolean CountDownTimer()
{
  static unsigned long duration = 1000000; // 1 second
  timeFlag = false;

  if (!Stop && !Paused) // if not Stopped or Paused, run timer
  {
    // check the time difference and see if 1 second has elapsed
    if ((_micro = micros()) - time > duration )
    {
      Clock--;
      timeFlag = true;

      if (Clock == 0 || spCaptured == 3) // check to see if the clock is 0
      {

        Stop = true; // If so, stop the timer
        clearLeds();
        //delay(5000);

        bigMessage = "END";


        if ( haveexternalleds == true ) {
          startfromLed = internalLeds;
        }

        if (gamesPlayed < internalLeds + externalLeds)
        {
          gamesPlayed++;
        }
        else
        {
          gamesPlayed = 1;
        }

        if (pointsRed < pointsBlue && mode != 4 )
        {
          for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
          {
            colourBlue();
          }
          smallMessage1 = String(pointsBlue) + String("  "); // makes no sense but I can't take the second string out otherwise the program fails

        }
        else if ( pointsRed > pointsBlue && mode != 4 )
        {


          for (whiteLed = startfromLed; whiteLed < internalLeds + externalLeds; whiteLed = whiteLed + 1)
          {
            colourRed();
          }
          smallMessage1 =  String(pointsRed);
        }
        else
        {

          if (pointsBlue > 250 * internalLeds)
          {
            ledsUp = internalLeds + externalLeds - startfromLed;
          }
          else
          {
            ledsUp = pointsBlue / 250;
            ledsUp++;
          }

          for (whiteLed = startfromLed; whiteLed < ledsUp ; whiteLed = whiteLed + 1)
          {
            if (spCaptured == 3)
            {
              colourRed();
            }
            else
            {
              colourYellow();
            }
          }
          if (mode == 4)
          {
            bigMessage = "END";
          }
          else
          {
            bigMessage = "TIE";
          }
          smallMessage1 =  String(pointsBlue);
        }
        smallMessage2 = "Wait";

        display.setTextSize(2);
        display.setCursor(0, 0);
        display.setTextColor(BLACK, WHITE);
        display.println(bigMessage);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.println( smallMessage1 );
        display.println( smallMessage2 );
        display.display();
        display.clearDisplay();
        delay( ( (timerMin * 60000) + (timerSec + 1000) ) / 2);
        // delay(10000);
        gameReset();
        configured = 2;

      }


      // check to see if micros() has rolled over, if not,
      // then increment "time" by duration
      _micro < time ? time = _micro : time += duration;
    }
  }
  return !Stop; // return the state of the timer
}

int spdifficultysetting()
{
  if ( haveexternalleds == true )
  {
    spdifficulty = externalLeds * 10 / spLevel * 20;

  }
  else if ( haveexternalleds == false )
  {
    spdifficulty = internalLeds * 10 / spLevel * 20;
  }
}



