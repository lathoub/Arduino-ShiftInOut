#pragma once

// 8-Bit Serial-In, Parallel-Out Shift

/*
*/

template<class DigitalPin, uint8_t size>
class IC74HC595 {
private:
  DigitalPin _clock; // CP
  DigitalPin _latch; // PE
  DigitalPin _data;  // DS
    
  void shiftOut()
  {
  }

  public:
  // Constructor
  IC74HC595(uint8_t pinClock, uint8_t pinLatch, uint8_t pinData)
  {
    _clock.pin(pinClock, OUTPUT);
    _latch.pin(pinLatch, OUTPUT);
    _data.pin (pinData,  OUTPUT);

    _clock.write(LOW);
    _latch.write(LOW);
    _data.write(LOW);
  }

  // read from <amount> IC's
  void write(uint8_t amount)
  {
  }

};
