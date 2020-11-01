#pragma once

// 1• 8-Bit Serial-In, Parallel-Out Shift

template <class Hardware>
class sipoInterface {
  public:
    sipoInterface(Hardware& hardware)
        : _hardware(hardware) 
    {
    }

    uint8_t* write(uint8_t amount) {
      return _hardware.write(amount);
    }

  private:
    Hardware& _hardware;
};
