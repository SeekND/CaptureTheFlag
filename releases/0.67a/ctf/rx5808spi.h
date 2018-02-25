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

// rx5808 module needs >30ms to tune.
#define MIN_TUNE_TIME 30

void setupSPIpins() {
  // SPI pins for RX control
  pinMode (slaveSelectPin, OUTPUT);
  pinMode (spiDataPin, OUTPUT);
  pinMode (spiClockPin, OUTPUT);
}

void SERIAL_SENDBIT1() {
  digitalLow(spiClockPin);
  delayMicroseconds(1);

  digitalHigh(spiDataPin);
  delayMicroseconds(1);
  digitalHigh(spiClockPin);
  delayMicroseconds(1);

  digitalLow(spiClockPin);
  delayMicroseconds(1);
}

void SERIAL_SENDBIT0() {
  digitalLow(spiClockPin);
  delayMicroseconds(1);

  digitalLow(spiDataPin);
  delayMicroseconds(1);
  digitalHigh(spiClockPin);
  delayMicroseconds(1);

  digitalLow(spiClockPin);
  delayMicroseconds(1);
}

void SERIAL_ENABLE_LOW() {
  delayMicroseconds(1);
  digitalLow(slaveSelectPin);
  delayMicroseconds(1);
}

void SERIAL_ENABLE_HIGH() {
  delayMicroseconds(1);
  digitalHigh(slaveSelectPin);
  delayMicroseconds(1);
}

uint16_t setModuleFrequency(uint16_t frequency) {
  uint8_t i;
  uint16_t channelData;

  channelData = frequency - 479;
  channelData /= 2;
  i = channelData % 32;
  channelData /= 32;
  channelData = (channelData << 7) + i;

  // bit bang out 25 bits of data
  // Order: A0-3, !R/W, D0-D19
  // A0=0, A1=0, A2=0, A3=1, RW=0, D0-19=0
  cli();
  SERIAL_ENABLE_HIGH();
  delayMicroseconds(1);
  SERIAL_ENABLE_LOW();

  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT1();

  SERIAL_SENDBIT0();

  // remaining zeros
  for (i = 20; i > 0; i--) {
    SERIAL_SENDBIT0();
  }

  // Clock the data in
  SERIAL_ENABLE_HIGH();
  delayMicroseconds(1);
  SERIAL_ENABLE_LOW();

  // Second is the channel data from the lookup table
  // 20 bytes of register data are sent, but the MSB 4 bits are zeros
  // register address = 0x1, write, data0-15=channelData data15-19=0x0
  SERIAL_ENABLE_HIGH();
  SERIAL_ENABLE_LOW();

  // Register 0x1
  SERIAL_SENDBIT1();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();
  SERIAL_SENDBIT0();

  // Write to register
  SERIAL_SENDBIT1();

  // D0-D15
  //   note: loop runs backwards as more efficent on AVR
  for (i = 16; i > 0; i--) {
    // Is bit high or low?
    if (channelData & 0x1) {
      SERIAL_SENDBIT1();
    }
    else {
      SERIAL_SENDBIT0();
    }
    // Shift bits along to check the next one
    channelData >>= 1;
  }

  // Remaining D16-D19
  for (i = 4; i > 0; i--) {
    SERIAL_SENDBIT0();
  }

  // Finished clocking data in
  SERIAL_ENABLE_HIGH();
  delayMicroseconds(1);

  digitalLow(slaveSelectPin);
  digitalLow(spiClockPin);
  digitalLow(spiDataPin);
  sei();

  delay(MIN_TUNE_TIME);

  return frequency;
}

uint16_t setModuleChannel(uint8_t channel, uint8_t band) {
  uint16_t frequency = pgm_read_word_near(channelFreqTable + channel + (8 * band));
  return setModuleFrequency(frequency);
}


int channelScan_allchannels()
{
  if ( channelIndex < numberPilots + 1 )
  {
    if (runloop < 10 ) // (CC) running a int loop 10x to give some time to the receiver to pickup any RSSI's. I found if I didn't do this it would change the channel to quickly and not find any RSSI. If you know any other way that this would work let me know :)
    {
      runloop++;
    }
    if (runloop >= 10)  //(CC) once runloop gets to 10 it will go up one channel and reset the runloop to 0 (in order to change to the next channel and so on)
    {
      channelIndex++;
      frequency = setModuleChannel(channelIndex, bandIndex);
      runloop = 0;
    }
  }
  else if ( channelIndex == numberPilots + 1 ) // (CC) once it gets to the max channels it will reset back to the first channel. This is set in RACEBAND band.
  {
    channelIndex = 0;
    frequency = setModuleChannel(channelIndex, bandIndex);
    runloop = 0;
    //delay(1000);
  }
}

