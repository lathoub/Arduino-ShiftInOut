#pragma once

// wrapper around system digital access pins

template <uint8_t pin, uint8_t mode>
class NativeDigitalIO
{
public:
  NativeDigitalIO()
  {
    ::pinMode(pin, mode);
  }

  uint8_t read()
  {
    return ::digitalRead(pin);
  };

  void write(uint8_t value)
  {
    ::digitalWrite(pin, value);
  };
};
