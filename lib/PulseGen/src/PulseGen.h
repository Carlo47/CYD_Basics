#pragma once

#include <Arduino.h>

class PulseGen
{
    public:
        PulseGen(uint8_t pin) : _pin(pin) { pinMode(_pin, OUTPUT); }
        PulseGen(uint8_t pin, uint32_t usPeriod) : _pin(pin), _usPeriod(usPeriod) { pinMode(_pin, OUTPUT); }
        PulseGen(uint8_t pin, uint32_t usPeriod, uint32_t usPulseWidth) : _pin(pin), _usPeriod(usPeriod), _usPulseWidth(usPulseWidth) { pinMode(_pin, OUTPUT); }
        PulseGen(uint8_t pin, uint32_t usPeriod, uint32_t usPulseWidth, uint32_t usPhase) : _pin(pin), _usPeriod(usPeriod), _usPulseWidth(usPulseWidth), _usPhase(usPhase) { pinMode(_pin, OUTPUT); }
        void loop();
        void on();
        void off();
        void setPhase(uint32_t usPhase);
        void setPeriod(uint32_t usPeriod);
        void setPulseWidth(uint32_t usPulseWidth);
        void setInvertedOutput(bool inverted);

    private:
        uint8_t _pin;
        uint32_t _usPeriod = 1000000;
        uint32_t _usPhase  = 250000;
        uint32_t _usPulseWidth = 10000;
        uint32_t _msPrevious = 0;
        bool     _isEnabled = false;
        bool     _isInverted = false;
};