#pragma once

/*
The 74HC165; 74HCT165 are 8-bit serial or parallel-in/serial-out shift registers. 
The device features a serial data input (DS), eight parallel data inputs (D0 to D7) 
and two complementary serial outputs (Q7 and Q7). When the parallel load input (PL)
is LOW the data from D0 to D7 is loaded into the shift register asynchronously. 
When PL is HIGH data enters the register serially at DS. When the clock enable input (CE) 
is LOW data is shifted on the LOW-to-HIGH transitions of the CP input. A HIGH on CE will 
disable the CP input. Inputs are overvoltage tolerant to 15 V. This enables the device 
to be used in HIGH-to-LOW level shifting applications.
*/

// The chip enable (/CE) pin is connected to ground as the chip may as well always be enabled

template <class PinLoad, class PinData, class PinClock>
class IC74HC165
{
private:
  // PinClockEnable& CE;
  PinLoad &PL;
  PinData &DS;
  PinClock &CP; // SCK

  const uint8_t _pulseWidth = 5; // in microseconds, datasheet indicates is 5 microseconds
  
  #define BITSPERBYTE 8

public:
  // Constructor
  IC74HC165(PinLoad &load, PinData &data, PinClock &clock)
      : PL(load), DS(data), CP(clock)
  {
  }

  void beginRead()
  {
    //   CE.write(HIGH);
    PL.write(LOW);
    delayMicroseconds(_pulseWidth);
    PL.write(HIGH);
    //    CE.write(LOW);
  }

  uint8_t read()
  {
    uint8_t result = 0;

    for (uint8_t i = 0; i < BITSPERBYTE; i++)
    {
      auto value = DS.read();
      result |= (value << ((BITSPERBYTE - 1) - i));

      CP.write(HIGH);
      delayMicroseconds(_pulseWidth);
      CP.write(LOW);
    }

    return result;
  }

  void endRead()
  {
  }
};

#define CREATE_74HC165(Name, DigitalIO, LatchPin, DataPin, ClockPin, MaxChipCount)   \
  DigitalIO<LatchPin, OUTPUT> latch##Name;                                           \
  DigitalIO<DataPin, INPUT> data##Name;                                              \
  DigitalIO<ClockPin, OUTPUT> clock##Name;                                           \
  IC74HC165<DigitalIO<LatchPin, OUTPUT>, DigitalIO<DataPin, INPUT>, DigitalIO<ClockPin, OUTPUT>> chip##Name(latch##Name, data##Name, clock##Name); \
  ShiftIn<IC74HC165<DigitalIO<LatchPin, OUTPUT>, DigitalIO<DataPin, INPUT>, DigitalIO<ClockPin, OUTPUT>>, MaxChipCount> Name(chip##Name);

#include <NativeDigitalIO.h>

#define CREATE_NATIVE_74HC165(Name, LatchPin, DataPin, ClockPin, MaxChipCount) \
  CREATE_74HC165(Name, NativeDigitalIO, LatchPin, DataPin, ClockPin, MaxChipCount);
