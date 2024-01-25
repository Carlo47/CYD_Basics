
#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"

extern int color[];
extern int nbrOfColors;
extern int rainbowColor[];
extern int nbrOfRainbowColors;

void sort3(uint8_t &a, uint8_t &b, uint8_t &c)
{
  if (a > b) std::swap(a, b);
  if (b > c) std::swap(b, c);
  if (a > b) std::swap(a, b);
}


/**
 * Convert RGB values (0..255) to HSV values using integer math
 * 0 <= H < 360, 0 <= S,V <= 100
*/
void rgb2hsv(uint8_t r, uint8_t g, uint8_t b, uint32_t &h, uint32_t &s, uint32_t &v)
{
  constexpr uint32_t Chernov_E = 65537u;
  constexpr uint32_t Chernov_S_MAX = 65535u;
  constexpr uint32_t Chernov_H_MAX = 393222u;

  uint8_t mn  = r;
  uint8_t mid = g;
  uint8_t mx  = b;
  uint8_t i;
  sort3(mn, mid, mx);

  v = mx;
  uint32_t d = mx - mn;
  if (d == 0) { h = 0; s = 0; v = v * 100 / 255; return; }

  if      (mx == r && mn == b) i = 0 ;
  else if (mx == g && mn == b) i = 1;
  else if (mx == g && mn == r) i = 2;
  else if (mx == b && mn == r) i = 3;
  else if (mx == b && mn == g) i = 4;
  else                         i = 5;

  s = ((d << 16) - 1) / v;

  uint32_t f = (((mid - mn) << 16) / d) + 1;

  if (i == 1 || i == 3 || i == 5) f = Chernov_E - f;
  h = (Chernov_E * i) + f;
  h = h * 360 / Chernov_H_MAX;
  s = s * 100 / Chernov_S_MAX;
  v = v * 100 / 255;
}


/**
 * Convert a HSV color to a rgb565 16 bit value rrrrrggggggbbbbb
 * 0 <= h < 360, 0.0 <= s,v <= 1.0
*/
void HSVtoRGB565(uint16_t &rgb565, uint16_t h, float s, float v )
{
  uint16_t R,G,B;
  float r,g,b, f,p,q,t;
  float hf = (float)h / 360.0;
  int    i = floor(hf * 6.0);

  f = hf * 6.0 - i;  
  p = v * (1.0 - s);
  q = v * (1 - f * s);
  t = v * (1 - (1 - f) * s);

  switch (i % 6)
  {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }

  R = r * 255.0;
  G = g * 255.0;
  B = b * 255.0;

  //rgb565 = (((R & 0b11111000)<<8) | ((G & 0b11111100)<<3) | (B>>3));
  rgb565 = ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);
}


/**
 * Draws horizontal gradient lines from left to the diagonal (top-left, bottem-right)
 * and vertical gradient lines from top to the diagonal
*/
void colorGradients(LGFX &lcd)
{
  int w = lcd.width();
  int h = lcd.height();
  lcd.fillScreen(TFT_RED);

  for (int y = 0; y < h; ++y)
  {
    lcd.drawGradientHLine(0,     y, y*w/h, TFT_GREEN, TFT_RED); // horizontal line from left to the diagonal
    lcd.drawGradientVLine(y*w/h, 0, y,     TFT_BLUE,  TFT_RED); // vertical   line from top  to the diagonal
  }
}


/**
 * Draws a RBG boarder around the screen, each
 * color is 2 pixel wide. Blue is in the middle.
*/
void rgbFrame(LGFX &lcd)
{
  lcd.drawRect(0, 0, lcd.width(),    lcd.height(),    TFT_RED);
  lcd.drawRect(1, 1, lcd.width()-2,  lcd.height()-2,  TFT_RED);
  lcd.drawRect(2, 2, lcd.width()-4,  lcd.height()-4,  TFT_BLUE);
  lcd.drawRect(3, 3, lcd.width()-6,  lcd.height()-6,  TFT_BLUE);
  lcd.drawRect(4, 4, lcd.width()-8,  lcd.height()-8,  TFT_GREEN);
  lcd.drawRect(5, 5, lcd.width()-10, lcd.height()-10, TFT_GREEN);
}


/**
 * Fills the screen with rgb colored tiles
 * The orientation of the display is Portrait
*/
void rgbTiles(LGFX &lcd)
{
  lcd.fillScreen(TFT_BLACK);

  int s = lcd.width() / 3;
  int origin_x = 0, origin_y = 0;
  int rgb[] = {TFT_RED, TFT_GREEN, TFT_BLUE};
  int i = 0;

  for (int y = 0; y < 4; y++)
  {
    i = y;
    i %= 3;
    for (int x = 0; x < 3; x++)
    {
      lcd.fillRect(origin_x, origin_y, s, s, rgb[i]);
      i++;
      i %= 3;
      origin_x += s;
    }
    origin_x = 0;
    origin_y += s;
  }
  rgbFrame(lcd);
}


/**
 * Fills the screen with colored tiles.
 * The color runs through all 24 defined TFT colors
 * from TFT_BLACK to TFT_WHITE
 * The orientation of the display is Portrait
*/
void colorTiles(LGFX &lcd)
{
  int sx = lcd.width() / 4;
  int sy = lcd.height() / 6;
  int origin_x = 0, origin_y = 0;
  int col = 0;
  for (int y = 0; y < 6; y++ )
  {
    for (int x = 0; x < 4; x++)
    {
      lcd.fillRect(origin_x, origin_y, sx, sy, color[col]);
      col++;
      origin_x += sx;
    }
    origin_x = 0;
    origin_y += sy;    
  }
}


void rainbowStripes(LGFX &lcd)
{
  int sx = lcd.width();
  int sy = lcd.height() / 7;
  int origin_x = 0, origin_y = 0;
  int col = 0;
  lcd.fillScreen(TFT_BLACK);
  for (int y = 0; y < 7; y++ )
  {
    lcd.fillRect(origin_x, origin_y, sx, sy, rainbowColor[col]);
    col++;
    origin_y += sy;    
  }
}


/**
 * Random random color dots
*/
void randomDots(LGFX &lcd)
{
  lcd.fillScreen(TFT_BLACK);
  
  for(unsigned int i = 0; i < 32000; i++)
  {
    int x = random(0, lcd.width());
    int y = random(0, lcd.height());
    lcd.fillCircle(x, y, random(1, 12), color[random(0,nbrOfColors)]);  
  }
  rgbFrame(lcd);
}


/**
 * Draws shrinking rectangles
*/
void rectangles(LGFX &lcd)
{
  lcd.fillScreen(TFT_BLACK);

  int w = lcd.width();
  int h = lcd.height();

  for (int i = 0; i < w/2; i += 5)
  {
    lcd.drawRect(i, i, w-2*i, h-2*i, color[random(0,nbrOfColors)]);
    delay(50);  
  }
  rgbFrame(lcd);
}


/**
 * Draws rounded rectangles
*/
void roundRectangles(LGFX &lcd) 
{
  lcd.fillScreen(TFT_BLACK);

  int w = lcd.width();
  int h = lcd.height();
  int rectH =40;
  int rectR = 15;

  for(int i = 0 ; i < w/2; i+=7) 
  {
    rectR = i+1;
    rectH = 2 * rectR;
    lcd.drawRoundRect(0, (h-rectH)/2, w, rectH, rectR, TFT_RED);
    lcd.drawRoundRect((w-rectH)/2, 0, rectH, h, rectR, TFT_MAGENTA);
    delay(50);
  }
  rgbFrame(lcd);
}


/**
 * Draws filled circles
*/
void circles(LGFX &lcd)
{
  lcd.fillScreen(TFT_BLACK);

  int w = lcd.width();
  int h = lcd.height();

  for(int i = 0; i < w/2; i += 3)
  {
    lcd.fillCircle(w/2, h/2, w/2 - 2*i, color[random(0,nbrOfColors)]);
    delay(50); 
  }
  rgbFrame(lcd);
}


/**
 * Draws triangles starting in each corner
*/
void triangles(LGFX &lcd)
{
  lcd.fillScreen(TFT_BLACK);

  int w = lcd.width()-1;
  int h = lcd.height()-1;
  
  for(int i = 0; i < 2*w/5; i += 5)
  {
    lcd.drawTriangle(w/2, 0, 0, h/2, i, i*h/w, TFT_RED);  
    lcd.drawTriangle(0, h/2, w/2, h, i, (w-i)*h/w, TFT_BLUE); 
    lcd.drawTriangle(w/2, 0, w, h/2, w-i, i*h/w, TFT_BLUE);  
    lcd.drawTriangle(w, h/2, w/2, h, w-i, (w-i)*h/w, TFT_RED); 
    delay(50);
  }
  rgbFrame(lcd);
}


/**
 * Display HSV color circle as a polygon with 120 sides.
 * The color value (H = Hue) changes from 0 ... 360° in steps of 3°.
 * Saturation (S) is set to 1.0 and brightness value (V) to 0.9 and  
 * not the maximum to avoid artifacts.
*/
void hsvColorCircle(LGFX &lcd)
{
  lcd.fillScreen(TFT_BLACK);

  float DEGTORAD = PI/180;
  int xm = lcd.width()  / 2;
  int ym = lcd.height() / 2;
  int xA, yA, xB, yB;
  int delta = 3;
  int radius = 100;

  uint16_t rgb565;
  
  for( int h = 0; h < 360; h += delta)
  {
    xA = xm + radius * sin(DEGTORAD * h);
    yA = ym + radius * cos(DEGTORAD * h);
    xB = xm + radius * sin(DEGTORAD * (h+delta));
    yB = ym + radius * cos(DEGTORAD * (h+delta)); 

    HSVtoRGB565(rgb565, h, 1.0, 0.9);
    lcd.fillTriangle(xm, ym, xA, yA, xB, yB, rgb565); 
  }
  rgbFrame(lcd);
}


/**
 * Integer conversion from RBG to HSV color space
 * https://gitlab.com/kibblab/rgb_to_hsv/-/blob/main/convert.py
 * 
 * 
 *  Chernov.E     = int(65537)
    Chernov.S_MAX = int(65535)
    Chernov.H_MAX = int(393222)

 *     def rgb_to_hsv_degrees(r: int, g: int, b: int) -> tuple[ int, int, int]:
        """Convert RGB to an integer representation of HSV."""
        k=[r,g,b]
        k.sort()
        mn, mid, mx = k

        v = mx
        d = mx - mn

        if d == 0:
            return 0, 0, v * 100 // 255
        
        if mx == r and mn == b:
            i=0
        elif mx == g and mn == b:
            i=1
        elif mx == g and mn == r:
            i=2
        elif mx == b and mn == r:
            i=3
        elif mx == b and mn == g:
            i=4
        else:
            i=5

        s = ((d << 16) - 1) // v

        f: int = (((mid - mn) << 16) // d) + 1

        if i == 1 or i == 3 or i == 5:
            f = Chernov.E - f

        h = (Chernov.E * i) + f
        return h * 360 // Chernov.H_MAX, s * 100 // Chernov.S_MAX , v * 100 // 255
*/


// https://github.com/y2kblog/bitmap-rgb565/blob/master/bmp_rgb565.c
/* static uint16_t convertRGBtoRGB565(uint8_t r, uint8_t g, uint8_t b)
{
    return  ((uint16_t) (r >> 3) << 11)
          | ((uint16_t) (g >> 2) << 5)
          |  (uint16_t) (b >> 3);
} */
