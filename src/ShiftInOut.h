#pragma once

#include <ShiftIn.h>
#include <ShiftOut.h>

#include <NativeDigitalIO.h>
#include <hardware/IC74HC165.h>
#include <hardware/IC74HC595.h>

#define CREATE_NATIVE_74HC165(Name, LatchPin, DataPin, ClockPin, MaxChipCount) \
  NativeDigitalIO<LatchPin, OUTPUT> latch##Name; \
  NativeDigitalIO<DataPin, INPUT> data##Name; \
  NativeDigitalIO<ClockPin, OUTPUT> clock##Name; \
  IC74HC165<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, INPUT>, NativeDigitalIO<ClockPin, OUTPUT>> chip##Name(latch##Name, data##Name, clock##Name); \
  ShiftIn<IC74HC165<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, INPUT>, NativeDigitalIO<ClockPin, OUTPUT>>, MaxChipCount> Name(chip##Name);

#define CREATE_NATIVE_74HC595(Name, LatchPin, DataPin, ClockPin, MaxChipCount) \
  NativeDigitalIO<LatchPin, OUTPUT> latch##Name; \
  NativeDigitalIO<DataPin, OUTPUT> data##Name; \
  NativeDigitalIO<ClockPin, OUTPUT> clock##Name; \
  IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>> chip##Name(latch##Name, data##Name, clock##Name); \
  ShiftOut<IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>>, MaxChipCount> Name(chip##Name);
