#pragma once

template <class Device, uint8_t totalChipCount>
class ShiftOut {
  public:
    ShiftOut(Device& device)
        : _device(device) 
    {
    }

    void write(uint8_t* buffer, uint8_t size) {
      _device.beginWrite();

      for (auto i = 0; i < size; i++)
        _device.write(buffer[i]);

      _device.endWrite();
    }

  private:
    Device& _device;
};

#include <hardware/IC74HC595.h>

#define CREATE_NATIVE_74HC595(Name, LatchPin, DataPin, ClockPin, MaxChipCount) \
  NativeDigitalIO<LatchPin, OUTPUT> latch##Name; \
  NativeDigitalIO<DataPin, OUTPUT> data##Name; \
  NativeDigitalIO<ClockPin, OUTPUT> clock##Name; \
  IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>> chip##Name(latch##Name, data##Name, clock##Name); \
  ShiftOut<IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>>, MaxChipCount> Name(chip##Name);
