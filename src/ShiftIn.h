#pragma once

template <class Device, uint8_t totalChipCount>
class ShiftIn {
  private:
    uint8_t _buffer[totalChipCount];

  public:
    ShiftIn(Device& device)
      :   _device(device)
    {
    }

    uint8_t* read(uint8_t chipCount) {

      _device.beginRead();

      for (auto i = 0; i < chipCount; i++)
        _buffer[i] = _device.read();

      _device.endRead();

      return _buffer;
    }

  private:
    Device& _device;
};
