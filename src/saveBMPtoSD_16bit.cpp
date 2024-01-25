#include <Arduino.h>
#include <SD.h>
#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"


bool saveToSD_16bit(LGFX &lcd, const char *filename, bool swapBytes=false)
{
  bool result = false;
  File file = SD.open(filename, "w");
  if (file)
  {
    int width  = lcd.width();
    int height = lcd.height();

    int rowSize = (2 * width + 3) & ~ 3;

    lgfx::bitmap_header_t bmpheader;
    bmpheader.bfType = 0x4D42;  // MB
    bmpheader.bfSize = rowSize * height + sizeof(bmpheader);
    bmpheader.bfOffBits = sizeof(bmpheader);

    bmpheader.biSize = 40;
    bmpheader.biWidth = width;
    bmpheader.biHeight = height;
    bmpheader.biPlanes = 1;
    bmpheader.biBitCount = 16;
    bmpheader.biCompression = 3;

    file.write((uint8_t*)&bmpheader, sizeof(bmpheader));
    uint8_t buffer[rowSize];
    memset(&buffer[rowSize - 4], 0, 4);
    for (int y = lcd.height() - 1; y >= 0; y--)
    {
      if (swapBytes)
      {
        lcd.readRect(0, y, lcd.width(), 1, (lgfx::swap565_t*)buffer);
      } 
      else
      {
        lcd.readRect(0, y, lcd.width(), 1, (lgfx::rgb565_t*)buffer);
      }
        
      file.write(buffer, rowSize);
    }
    file.close();
    result = true;
  }
  else
  {
    log_e("==> file open failed");
  }
  log_e("==> done");
  return result;
}