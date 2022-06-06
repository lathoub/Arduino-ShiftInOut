#pragma once

template <class Device, uint8_t totalICcount>
class ShiftOut
{
private:
  uint8_t _buffer[totalICcount];

public:
  ShiftOut(Device &device)
      : _device(device)
  {
  }

  void write(uint8_t *buffer, uint8_t chipCount = totalICcount)
  {
    // keep within bounds
    if (chipCount > totalICcount)
      chipCount = totalICcount;

    _device.beginWrite();

    for (auto i = chipCount - 1; i >= 0; i--)
      _device.write(buffer[i]);

    _device.endWrite();
  }

  ShiftOut &setAll(bool onOff)
  {
    for (auto i = totalICcount - 1; i >= 0; i--)
      _buffer[i] = (onOff) ? 0xFF : 0x00;
    return static_cast<ShiftOut &>(*this);
  }

  ShiftOut &set(uint8_t bit, bool onOff)
  {
    bitWrite(_buffer[bit / 8], bit - (8 * (bit / 8)), onOff);
    return static_cast<ShiftOut &>(*this);
  }

  void commit()
  {
    write(_buffer, totalICcount);
  }

private:
  Device &_device;
};