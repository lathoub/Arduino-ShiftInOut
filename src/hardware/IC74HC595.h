#pragma once

/*
*/

template <class PinLoad, class PinData, class PinClock>
class IC74HC595
{
private:
  PinLoad &PL;
  PinData &DS;
  PinClock &CP;

public:
  // Constructor
  IC74HC595(PinLoad &load, PinData &data, PinClock &clock)
      : PL(load), DS(data), CP(clock)
  {
  }

  void beginWrite()
  {
    PL.write(LOW);
  }

  void write(uint8_t value)
  {
    int pinState;

    for (auto i = 0; i < 8; i++)
    {
      CP.write(LOW);

      //if the value passed to myDataOut and a bitmask result
      // true then... so if we are at i=6 and our value is
      // %11010100 it would the code compares it to %01000000
      // and proceeds to set pinState to 1.
      if (value & (1 << i))
      {
        pinState = 1;
      }
      else
      {
        pinState = 0;
      }

      //Sets the pin to HIGH or LOW depending on pinState
      DS.write(pinState);
      //register shifts bits on upstroke of clock pin
      CP.write(HIGH);
      //zero the data pin after shift to prevent bleed through
      DS.write(LOW);
    }

    //stop shifting
    CP.write(LOW);
  }

  void endWrite()
  {
    PL.write(HIGH);
  }
};
