  #include "PulseGen.h"

void PulseGen::loop()
{
    if (_isEnabled)
    {
      if (_isInverted)
        digitalWrite(_pin, (micros() - _usPhase) % _usPeriod < _usPulseWidth ? HIGH : LOW);
      else
        digitalWrite(_pin, (micros() - _usPhase) % _usPeriod < _usPulseWidth ? LOW : HIGH);
    }
}

void PulseGen::off()
{
  _isEnabled = false;
  _isInverted ? digitalWrite(_pin, LOW) : digitalWrite(_pin, HIGH);
}

void PulseGen::on()
{
  _isEnabled = true;
  _isInverted ? digitalWrite(_pin, LOW) : digitalWrite(_pin, HIGH);
}

void PulseGen::setPhase(uint32_t usPhase)
{
  _usPhase = usPhase;
}

void PulseGen::setPeriod(uint32_t usPeriod)
{
  _usPeriod = usPeriod;
}

void PulseGen::setPulseWidth(uint32_t usPulseWidth)
{
  _usPulseWidth = usPulseWidth;
}

void PulseGen::setInvertedOutput(bool inverted)
{
  _isInverted = inverted;
}