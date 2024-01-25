#include <Arduino.h>
#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"
#include <SPI.h>

using Action = void(&)(LGFX &lcd);

void donothing(LGFX &lcd){};

void calibrateTouch(LGFX &lcd)
  {
    lcd.setTextSize((std::max(lcd.width(), lcd.height()) + 255) >> 8);

    // Calibrate when touch is available. (Can be omitted.)
    if (lcd.touch())
    {
        //if (lcd.width() < lcd.height()) lcd.setRotation(lcd.getRotation() ^ 1);

        // Draws guidance text on the screen
        lcd.setTextDatum(textdatum_t::middle_center);
        lcd.setTextSize(1.0);
        lcd.clear();
        lcd.drawString("touch the arrow marker.", lcd.width()>>1, lcd.height() >> 1);
        lcd.setTextDatum(textdatum_t::top_left);

        // When using touch, perform calibration. Touch the tips of the arrows 
        // that appear in the four corners of the screen in sequence.
        uint16_t fg = TFT_WHITE;
        uint16_t bg = TFT_BLACK;
        if (lcd.isEPD()) std::swap(fg, bg);
        uint16_t calData[8];
        lcd.calibrateTouch(calData, fg, bg, std::max(lcd.width(), lcd.height()) >> 3);
        for (int i = 0; i < 8; i++)
        {
          Serial.printf("%3d\n", calData[i]);
        }
    }
    log_e("==> done");
  }


/**
 * Draw a framed crosshair in portrait orientation
*/
void framedCrosshair(LGFX &lcd)
{
  char str[24]; 
  lcd.drawRect(0,0, lcd.width(), lcd.height(), TFT_RED);
  lcd.drawLine(0,0, lcd.width(), lcd.height(), TFT_GREEN);
  lcd.drawLine(lcd.width(),0, 0, lcd.height(), TFT_BLUE);
  lcd.fillRect(0,0, 20, 20, TFT_GREEN);
  lcd.fillRect(lcd.width()-10,lcd.height()-10, 10, 10, TFT_RED);;
  lcd.setTextSize(1.0);
  sprintf(str, "top left, rot=%d", lcd.getRotation());
  lcd.drawString(str, 25,0);
}


/**
 * Show some facts about the display
*/
void lcdInfo(LGFX &lcd)
{
  Serial.printf(R"(
LCD Info
--------
  width x height = %d x %d, 
  rotation       = %d, 
  color depth    = %d 
  text size X    = %4.2f
  text size Y    = %4.2f
)", lcd.width(), lcd.height(), lcd.getRotation(), lcd.getColorDepth(),
    lcd.getTextSizeX(), lcd.getTextSizeY() );
}


/**
 * Initialize display and call the greeting function.
 * The default for greeting is donothing(). To calibrate the 
 * touchscreen call it as initDisplay(lcd, calibrateTouch).
 * The greeting function takes as argument the passed lcd
*/
void initDisplay(LGFX &lcd, Action greet=donothing)
  {
    lcd.begin();
    lcd.fillScreen(TFT_BLACK);
    lcd.setTextSize(1.0);
    lcd.setTextDatum(lgfx::textdatum::TL_DATUM);
    lcd.setFont(&lgfx::v1::fonts::DejaVu18);
    greet(lcd);
  }
