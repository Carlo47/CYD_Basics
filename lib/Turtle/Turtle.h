/**
 * Implements some Turtle Graphic primitives
 * 
 * Turtle origin (0,0) is at upper left corne of the lcd
 * Turtle heading 0.0 degrees is to the right in positive x direction
*/

#pragma once
#include <Arduino.h>
#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"

class Turtle
{
    static constexpr float RAD = 3.14159265359 / 180.0;

    public:
        Turtle(LGFX &lcd, float heading, int x0, int y0, int penColor=TFT_WHITE) : 
            _lcd(lcd), _heading(heading), _x(x0), _y(y0), _penColor(penColor)
        { lcd.fillScreen(_screenColor); }

        LGFX  &_lcd;
        void clear();
        void forward(float step);
        void backward(int step);
        void right(float angle);
        void left(float angle);
        void home(int x, int y, float heading);
        void moveTo(int x, int y);
        void penDown();
        void penUp();
        void penColor(int color);
        void screenColor(int color);
        void showValues();
        void bresenham(int x, int y, int x1, int y1);

    private:
        float _heading; // heading in degrees
        int   _x;       // x position on screen
        int   _y;       // y position on screen 
        int   _penColor;
        int   _screenColor = TFT_BLACK;
        bool  _penDown = true;  
};
