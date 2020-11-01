#pragma once

// parallel-in/serial out

template <class Hardware>
class pisoInterface {
  public:
    pisoInterface(Hardware& hardware)
        : _hardware(hardware) 
    {
    }

    uint8_t* read(uint8_t amount) {
      return _hardware.read(amount);
    }

  private:
    Hardware& _hardware;
};
