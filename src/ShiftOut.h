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
