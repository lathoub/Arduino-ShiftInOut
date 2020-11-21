#pragma once

#define BITSINABYTE 8
#define TYPESIZE (sizeof(type) * BITSINABYTE)

template <class type, uint8_t size>
class LightManager
{
  private:
    uint8_t lightsState[TYPESIZE * size]; 

  public:

    uint8_t* buffer()
    {
        return lightsState;
    }

    void all(bool onOff)
    {
        memset(lightsState, onOff, size * sizeof(type));
    }

    void set(uint8_t pinNr, bool onOff)
    {
      bitWrite(lightsState[pinNr / 8], pinNr - (8 * (pinNr / 8)), onOff);
    }
};