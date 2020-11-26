#pragma once

/*
The 74HC165; 74HCT165 are 8-bit serial or parallel-in/serial-out shift registers. 
The device features a serial data input (DS), eight parallel data inputs (D0 to D7) 
and two complementary serial outputs (Q7 and Q7). When the parallel load input (PL)
is LOW the data from D0 to D7 is loaded into the shift register asynchronously. 
When PL is HIGH data enters the register serially at DS. When the clock enable input (CE) 
is LOW data is shifted on the LOW-to-HIGH transitions of the CP input. A HIGH on CE will 
disable the CP input. Inputs are overvoltage tolerant to 15 V. This enables the device 
to be used in HIGH-to-LOW level shifting applications.
*/

// The chip enable (/CE) pin is connected to ground as the chip may as well always be enabled

template <class PinLoad, class PinData, class PinClock>
class IC74HC165
{
private:
  // PinClockEnable& CE;
  PinLoad &PL;
  PinData &DS;
  PinClock &CP; // SCK

  uint8_t _pulseWidth; // in microseconds, default is 5

public:
  // Constructor
  IC74HC165(PinLoad &load, PinData &data, PinClock &clock)
      : PL(load), DS(data), CP(clock),
        _pulseWidth(5)
  {
  }

  void beginRead()
  {
    //   CE.write(HIGH);
    PL.write(LOW);
    delayMicroseconds(_pulseWidth);
    PL.write(HIGH);
    //    CE.write(LOW);
  }

  uint8_t read()
  {
    uint8_t result = 0;

    for (auto i = 0; i < 8; i++)
    {
      auto value = DS.read();
      result |= (value << ((8 - 1) - i));

      CP.write(HIGH);
      delayMicroseconds(_pulseWidth);
      CP.write(LOW);
    }

    return result;
  }

  void endRead()
  {
  }
};
