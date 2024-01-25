#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"

extern int color[];
extern int nbrOfColors;


/**
 * Draws a self-similar fractal pattern known as "Barnsleys Fern" 
*/
void barnsleyFern(LGFX &lcd) 
{
  uint8_t savedRotation = lcd.getRotation(); 
  float x = 0;
  float y = 0;

  lcd.fillScreen(TFT_BLACK);
  lcd.setRotation(0); // Set orienation to Portrait

  for (unsigned int i = 0; i < 32000; i++) 
  {
    float xt = 0;
    float yt = 0;
 
    int r = random(0, 100);
 
    if (r <= 1) 
    {
      xt = 0;
      yt = 0.16*y;
    } else if (r <= 8) 
    {
      xt = 0.20*x - 0.26*y;
      yt = 0.23*x + 0.22*y + 1.60;
    } else if (r <= 15) 
    {
      xt = -0.15*x + 0.28*y;
      yt =  0.26*x + 0.24*y + 0.44;
    } else 
    {
      xt =  0.85*x + 0.04*y;
      yt = -0.04*x + 0.85*y + 1.60;
    }
 
    x = xt;
    y = yt;
 
    int m = round(lcd.width()/2 + 32*x);
    int n = lcd.height()-round(30*y);
 
    lcd.drawPixel(m, n, TFT_GREEN);
  }
  lcd.setRotation(savedRotation);
  lcd.drawRect(0, 0, lcd.width(), lcd.height(), TFT_GOLD);
}


/**
 * Draws a fractal pattern known as "Mandelbrot's Apple Man"
*/
void mandelbrot(LGFX &lcd)
{
  uint8_t savedRotation = lcd.getRotation();
  int maxIteration = 1000;
  int w = lcd.width();
  int h = lcd.height();
  int farbe;
  lcd.setRotation(0); // Set orientation to Portrait
  lcd.fillScreen(TFT_WHITE);

  for(int zeile = 0; zeile < h; zeile++)
  {
    for(int spalte = 0; spalte < w; spalte++)
    {
      float c_re = (spalte - w/2.0) * 4.0 / w;
      float c_im = (zeile- h/2.0) * 4.0 / h;
      float x = 0;
      float y = 0;
      int iteration = 0;
      while (x*x + y*y <=4 && iteration < maxIteration)
      {
        float x_neu = x*x - y*y + c_re;
        y = 2*x*y + c_im;
        x = x_neu;
        iteration++;
      }
      if (iteration < maxIteration)
      {
        if (iteration < nbrOfColors) farbe = color[iteration];
        else farbe = TFT_WHITE;
        lcd.drawPixel(spalte, zeile, farbe);
      }
      else
          lcd.drawPixel(spalte, zeile, TFT_BLACK);
    }
  }
  lcd.setRotation(savedRotation);
  lcd.drawRect(0, 0, lcd.width(), lcd.height(), TFT_GOLD);
}

/**
 * Draws the fractal known as "Sierpinskys Triangle"
 * Method: 
 * 1) Place 3 corner points randomly
 * 2) Chose another point randomly, e.g P(20, 20)
 * 3) Select a corner randomly and mark the middle between the corner and point P
 * 4) The middle becomes the new point P
 * 5) Repeat from 3) 
*/
void sierpinskyTriangle(LGFX &lcd)
{
  int ecke[3][2] = {{0,0}, {lcd.width(),0}, {lcd.width()/2,lcd.height()}};
  int farbe[] = {TFT_RED, TFT_BLUE, TFT_GREEN};
  int p[] = {20,20};
  int k, x, y, mx, my;
  
  lcd.fillScreen(TFT_BLACK);
  for(int i = 0; i < 32000; i++)
  {
    k = random(0,3);
    x = ecke[k][0];
    y = ecke[k][1];
    mx = (x-p[0])/2 + p[0]; 
    my = (y-p[1])/2 + p[1];
    lcd.drawPixel(mx, my, farbe[k]);
    p[0] = mx;
    p[1] = my;
  }
  lcd.drawRect(0, 0, lcd.width(), lcd.height(), TFT_GOLD);
}
