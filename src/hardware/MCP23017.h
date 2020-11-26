#pragma once

/*
*/

template <class PinLoad, class PinData, class PinClock>
class MCP23017
{
private:
  PinLoad &PL;
  PinData &DS;
  PinClock &CP; // SCK

  uint8_t _pulseWidth; // in microseconds, default is 5

public:
  // Constructor
  MCP23017(PinLoad &load, PinData &data, PinClock &clock)
      : PL(load), DS(data), CP(clock),
        _pulseWidth(5)
  {
  }

  void beginRead()
  {
  }

  uint16_t read()
  {
    uint16_t result = 0;

    return result;
  }

  void endRead()
  {
  }
};
