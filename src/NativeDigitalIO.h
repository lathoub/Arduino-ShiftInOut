#pragma once

class NativeDigitalIO
{
  private:
     uint8_t _pin;

public:
  void pin(uint8_t pin, uint8_t mode)
  {
    _pin = pin;
    ::pinMode(_pin, mode);
  }

  void write(uint8_t value) {
    ::digitalWrite(_pin, value); 
  };
  
  uint8_t read() {
    return ::digitalRead(_pin); 
  };
};