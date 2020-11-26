#pragma once

template <class Device, uint8_t totalChipCount>
class ShiftIn
{
private:
  uint8_t _buffer[totalChipCount];
  bool invert = true;

public:
  ShiftIn(Device &device)
      : _device(device)
  {
  }

  uint8_t *read(uint8_t chipCount = totalChipCount)
  {
    _device.beginRead();

    for (auto i = 0; i < chipCount; i++)
      _buffer[i] = _device.read();

    _device.endRead();

    if (invert)
      for (auto i = 0; i < chipCount; i++)
        _buffer[i] = ~_buffer[i];

    return _buffer;
  }

private:
  Device &_device;
};

#include <hardware/IC74HC165.h>

#define CREATE_NATIVE_74HC165(Name, LatchPin, DataPin, ClockPin, MaxChipCount)                                                                                       \
  NativeDigitalIO<LatchPin, OUTPUT> latch##Name;                                                                                                                     \
  NativeDigitalIO<DataPin, INPUT> data##Name;                                                                                                                        \
  NativeDigitalIO<ClockPin, OUTPUT> clock##Name;                                                                                                                     \
  IC74HC165<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, INPUT>, NativeDigitalIO<ClockPin, OUTPUT>> chip##Name(latch##Name, data##Name, clock##Name); \
  ShiftIn<IC74HC165<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, INPUT>, NativeDigitalIO<ClockPin, OUTPUT>>, MaxChipCount> Name(chip##Name);
