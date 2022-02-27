#pragma once

template <class Device, uint8_t totalICcount>
class ShiftIn
{
private:
  uint8_t _buffer[totalICcount];

public:
  ShiftIn(Device &device)
      : _device(device)
  {
  }

  uint8_t *read(uint8_t chipCount = totalICcount)
  {
    // keep within bounds
    if (chipCount > totalICcount)
      chipCount = totalICcount;

    // read from all IC's
    _device.beginRead();
    for (uint8_t i = 0; i < chipCount; i++)
      _buffer[i] = _device.read();
    _device.endRead();

      // tmp
      for (uint8_t i = 0; i < chipCount; i++)
        _buffer[i] = ~_buffer[i];

    return _buffer;
  }

private:
  Device &_device;
};