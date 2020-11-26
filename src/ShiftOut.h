#pragma once

template <class Device, uint8_t totalChipCount>
class ShiftOut
{
private:
  uint8_t _buffer[totalChipCount];
  bool _autoCommit;

public:
  ShiftOut(Device &device)
      : _device(device)
  {
  }

  void write(uint8_t *buffer, uint8_t chipCount = totalChipCount)
  {
    _device.beginWrite();

    for (int i = chipCount - 1; i >= 0; i--)
      _device.write(buffer[i]);

    _device.endWrite();
  }

  ShiftOut& setAll(bool onOff)
  {
    for (int i = totalChipCount - 1; i >= 0; i--)
      _buffer[i] = (onOff) ? 0xFF : 0x00;
    return static_cast<ShiftOut &>(*this);
  }

  ShiftOut& set(uint8_t bit, bool onOff)
  {
    bitWrite(_buffer[bit / 8], bit - (8 * (bit / 8)), onOff);
    return static_cast<ShiftOut &>(*this);
  }

  void commit()
  {
    write(_buffer, totalChipCount);
  }

private:
  Device &_device;
};

#include <hardware/IC74HC595.h>

#define CREATE_NATIVE_74HC595(Name, LatchPin, DataPin, ClockPin, MaxChipCount)                                                                                        \
  NativeDigitalIO<LatchPin, OUTPUT> latch##Name;                                                                                                                      \
  NativeDigitalIO<DataPin, OUTPUT> data##Name;                                                                                                                        \
  NativeDigitalIO<ClockPin, OUTPUT> clock##Name;                                                                                                                      \
  IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>> chip##Name(latch##Name, data##Name, clock##Name); \
  ShiftOut<IC74HC595<NativeDigitalIO<LatchPin, OUTPUT>, NativeDigitalIO<DataPin, OUTPUT>, NativeDigitalIO<ClockPin, OUTPUT>>, MaxChipCount> Name(chip##Name);
