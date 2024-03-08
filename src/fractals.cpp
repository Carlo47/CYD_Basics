#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"
#include "Turtle.h"

extern int color[];
extern int nbrOfColors;
constexpr float SQRT2 = 1.414213562373; 

/**
 * Spiral
 * 
 * Recipe: Go one step forward and then rotate by a certain angle. 
 * Repeat this with the step length reduced by delta until the step 
 * is smaller than delta.
*/
void spiral(Turtle &t, float angle, float step, float delta)
{
  t.forward(step);
  t.right(angle);
  if (step >= delta) 
    spiral(t, angle, step-delta, delta);
}

/**
 * Koch-Curve
 * The Koch Curve draws a third of a snowflake
 * 
 * Recipe: Take a line, divide it into 3 equal sections and build
 * an equilateral triangle over the middle section. Proceed in the
 * same way with the sections of the new figure. The resulting figure
 * contains itself in each section - it is self-similar.
*/
void koch(Turtle &t, int n, float step)
{
  if (n == 0)
  {
    t.forward(step);
  }
  else
  {
    koch(t, n-1, step/3.0); t.right(60.0);
    koch(t, n-1, step/3.0); t.left(120.0);
    koch(t, n-1, step/3.0); t.right(60.0);
    koch(t, n-1, step/3.0);
  }
}

/**
 * C-Curve
 * 
 * Recipe: Take a line and build a right-angled isosceles triangle over it.
 * Proceed in the same way with the sections of the new figure
*/
void cCurve(Turtle &t, int n, int step)
{
  if (n == 0)
  {
    t.forward(step);
  }
  else
  {
    t.right(45.0);
    cCurve(t, n-1, step/SQRT2);
    t.left(90.0);
    cCurve(t, n-1, step/SQRT2);
    t.right(45.0);
  }
}


/**
 * Dragon-Curve
 * 
 * Recipe: The procedure is the same as for the C-curve, but the triangles are 
 * built alternately on different sides of the sections. The parameter sign is 
 * introduced so that this alternation can be taken into account. It controls 
 * the change of direction for the turns.
*/
void dragonCurve(Turtle &t, int n, int sign, float step)
{
  if (n == 0)
  {
    t.forward(step);
  }
  else
  {
    t.right(sign * 45.0);
    dragonCurve(t, n-1, 1, step/SQRT2);
    t.left(sign * 90.0);
    dragonCurve(t, n-1, -1, step/SQRT2);
    t.right(sign * 45.0);
  }  
}

/**
 * Draws some spirals
*/
void spirals(Turtle &t)
{
  t.home(10, 10, 0.0); spiral(t, 89.0, 60.0, 1.5);
  t.home(90, 10, 0.0); spiral(t, 90.0, 60.0, 1.5);
  t.home(170, 10, 0.0); spiral(t, 91.0, 60.0, 1.5);

  t.home(10,  80, 0.0); spiral(t, 20.0, 20.0, 1);
  t.home(90,  80, 0.0); spiral(t, 30.0, 20.0, 1);
  t.home(170, 80, 0.0); spiral(t, 45.0, 20.0, 1);

  t.home(80, 170, 0.0); spiral(t, 75.0, 100.0, 1);
}


void sevenSpirals(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2, TFT_RED);
  t.screenColor(TFT_YELLOW);
  spirals(t);
}

/**
 * Draws Koch 1/3-snowflakes of order 0 to 4
*/
void kochSnowflakes01234(Turtle &t)
{ 
    t.home(30,  15, 0.0); koch(t, 0, 200); t._lcd.drawChar(48+0, 2, 15);
    t.home(30,  50, 0.0); koch(t, 1, 200); t._lcd.drawChar(48+1, 2, 50);
    t.home(30, 120, 0.0); koch(t, 2, 200); t._lcd.drawChar(48+2, 2, 120);
    t.home(30, 190, 0.0); koch(t, 3, 200); t._lcd.drawChar(48+3, 2, 190);
    t.home(30, 260, 0.0); koch(t, 4, 200); t._lcd.drawChar(48+4, 2, 260);
}


void fiveKochSnowflakes(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2);
  kochSnowflakes01234(t);
}


/**
 * Draws C-Curves of order 0 to 3
*/
void cCurves0123(Turtle &t)
{
  t.home(41,  15, 0.0); cCurve(t, 0, 160); t._lcd.drawChar(48+0, 2, 15);
  t.home(41,  40, 0.0); cCurve(t, 1, 160); t._lcd.drawChar(48+1, 2, 40);
  t.home(41,  90, 0.0); cCurve(t, 2, 160); t._lcd.drawChar(48+2, 2, 90);
  t.home(41, 190, 0.0); cCurve(t, 3, 160); t._lcd.drawChar(48+3, 2, 190);
}


void cCurves1(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2);
  cCurves0123(t);
}


/**
 * Draws C-Curves of order 4 to 6
*/
void cCurves456(Turtle &t)
{
  t.home(69,  15, 0.0); cCurve(t, 4, 120); t._lcd.drawChar(48+4, 2, 15);
  t.home(69, 120, 0.0); cCurve(t, 5, 120); t._lcd.drawChar(48+5, 2, 120);
  t.home(69, 225, 0.0); cCurve(t, 6, 120); t._lcd.drawChar(48+6, 2, 225);
}


void cCurves2(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2);
  cCurves456(t);
}


/**
 * Draws C-Curves of order 7 to 9
*/
void cCurves789(Turtle &t)
{
  t.home(69,  25, 0.0); cCurve(t, 7, 110); t._lcd.drawChar(48+7, 2, 25);
  t.home(69, 145, 0.0); cCurve(t, 8, 110); t._lcd.drawChar(48+8, 2, 145);
  t.home(69, 245, 0.0); cCurve(t, 9, 110); t._lcd.drawChar(48+9, 2, 245);
}


void cCurves3(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2);
  cCurves789(t);
}


/**
 * Draws Dragon-Curves of order 0 to 3
*/
void dragonCurves0123(Turtle &t)
{
  t.home(60,  15, 0.0); dragonCurve(t, 0, 1, 150.0); t._lcd.drawChar(48+0, 2, 15);
  t.home(60,  40, 0.0); dragonCurve(t, 1, 1, 150.0); t._lcd.drawChar(48+1, 2, 40);
  t.home(60, 135, 0.0); dragonCurve(t, 2, 1, 150.0); t._lcd.drawChar(48+2, 2, 135);
  t.home(60, 235, 0.0); dragonCurve(t, 3, 1, 150.0); t._lcd.drawChar(48+3, 2, 235);
}


void dragonCurves1(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2);
  dragonCurves0123(t);
}


/**
 * Draws Dragon-Curves of order 4 to 6
*/
void dragonCurves456(Turtle &t)
{
  t.home(70,  32, 0.0); dragonCurve(t, 4, 1, 120.0); t._lcd.drawChar(48+4, 2, 32);
  t.home(70, 130, 0.0); dragonCurve(t, 5, 1, 120.0); t._lcd.drawChar(48+5, 2, 130);
  t.home(70, 240, 0.0); dragonCurve(t, 6, 1, 120.0); t._lcd.drawChar(48+6, 2, 240);
}


void dragonCurves2(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2);
  dragonCurves456(t);
}


/**
 * Draws Dragon-Curves of order 7 to 9
*/
void dragonCurves789(Turtle &t)
{
  t.home(70,  35, 0.0); dragonCurve(t, 7, 1, 100.0); t._lcd.drawChar(48+7, 2, 35);
  t.home(70, 140, 0.0); dragonCurve(t, 8, 1, 100.0); t._lcd.drawChar(48+8, 2, 140);
  t.home(70, 250, 0.0); dragonCurve(t, 9, 1, 100.0); t._lcd.drawChar(48+9, 2, 250);
}


void dragonCurves3(LGFX &lcd)
{
  Turtle t(lcd, 0.0, lcd.width()/2, lcd.height()/2);
  dragonCurves789(t);
}


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
