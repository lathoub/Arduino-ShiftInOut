#pragma once

/*
*/

template <class PinLoad, class PinData, class PinClock>
class IC74HC595
{
private:
  PinLoad &PL;
  PinData &DS;
  PinClock &CP;

  #define BITSPERBYTE 8

public:
  // Constructor
  IC74HC595(PinLoad &load, PinData &data, PinClock &clock)
      : PL(load), DS(data), CP(clock)
  {
  }

  void beginWrite()
  {
    PL.write(LOW);
  }

  void write(const uint8_t value)
  {
    uint8_t pinState;

    for (uint8_t i = 0; i < BITSPERBYTE; i++)
    {
      CP.write(LOW);

      pinState = (value & (1 << i));

      DS.write(pinState);
      //register shifts bits on upstroke of clock pin
      CP.write(HIGH);
      //zero the data pin after shift to prevent bleed through
      DS.write(LOW);
    }

    CP.write(LOW);
  }

  void endWrite()
  {
    PL.write(HIGH);
  }
};

#define CREATE_74HC595(Name, DigitalIO, LatchPin, DataPin, ClockPin, MaxChipCount)   \
  NativeDigitalIO<LatchPin, OUTPUT> latch##Name;                                     \
  NativeDigitalIO<DataPin, OUTPUT> data##Name;                                       \
  NativeDigitalIO<ClockPin, OUTPUT> clock##Name;                                     \
  IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>> chip##Name(latch##Name, data##Name, clock##Name); \
  ShiftOut<IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>>, MaxChipCount> Name(chip##Name);

#include <NativeDigitalIO.h>

#define CREATE_NATIVE_74HC595(Name, LatchPin, DataPin, ClockPin, MaxChipCount) \
  CREATE_74HC595(Name, NativeDigitalIO, LatchPin, DataPin, ClockPin, MaxChipCount);
