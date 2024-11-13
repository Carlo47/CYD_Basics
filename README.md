# First steps with the ESP32-2432S028R
I was interested in the ***Cheap Yellow Display*** or ***CYD*** as [Brian Lough](https://www.youtube.com/watch?v=0AVyvwv0agk) called it, because it combines an ESP32 with display, touchscreen, SD card reader, audio output, RGB LED and phototransistor on one board - and all for very little money.

After some research on the Internet, however, I soon realized that the board obviously has its peculiarities, not to say design flaws. All the more exciting to experiment with it!

I found the board definition *esp32-2432S028R.json* for PlatformIO [here](https://github.com/rzeldent/platformio-espressif32-sunton/) and put it with some modifications into my bords folder

A little later I realized that the graphical library [***LovyanGFX***](https://github.com/lovyan03/LovyanGFX) is the better choice for a display with touch function than the usually used library [*TFT_eSPI*](https://github.com/bodmer) from Bodmer.

The first thing I wanted to do was to build a small menu system with which I could display various graphic patterns on the screen and then save the images on the SD card as a RGB565 bitmap.

However, this project failed because I was unable to operate the display, touchscreen and SD card at the same time. Either the display and the touchscreen or the display and the SD card worked, but never all three together.

Operating the SD card or touchscreen on the SPI_HOST HSPI or VSPI or vice versa was also unsuccessful. Either I could operate the touchscreen but not save any bitmaps, or I could save bitmaps but the touchscreen did not respond.

Nevertheless, I made some graphics and saved them to the SD card as RGB565 bitmaps and converted them to png with XnView, so that i can show them in this README. To my great disappointment, the colors in the saved bitmaps did not match those on the screen, as these pictures show:

| Screen Photo | Bitmap RGB | Bitmap BRG |
|:------------:|:----------:|:----------:|
| ![img01](images/Photo/00_RGB_Tiles_Photo.png)   | ![img02](images/Screenshots/colors_saved_as_RGB/PNG/00_RGB_Tiles_16.png) | ![img03](images/Screenshots/colors_swapped_RGB_to_BRG/PNG/00_RGB_Tiles_16.png) |
| ![img11](images/Photo/01_Rainbow_Stripes_Photo.png)   | ![img12](images/Screenshots/colors_saved_as_RGB/PNG/01_Rainbow_Stripes_16.png) | ![img13](images/Screenshots/colors_swapped_RGB_to_BRG/PNG/01_Rainbow_Stripes_16.png) |
| ![img21](images/Photo/02_Color_Tiles_Photo.png)   | ![img22](images/Screenshots/colors_saved_as_RGB/PNG/02_Color_Tiles_16.png) | ![img23](images/Screenshots/colors_swapped_RGB_to_BRG/PNG/02_Color_Tiles_16.png) |
| ![img31](images/Photo/08_HSV_ColorCircle_Photo.png)   | ![img31](images/Screenshots/colors_saved_as_RGB/PNG/08_HSV_ColorCircle_16.png) | ![img31](images/Screenshots/colors_swapped_RGB_to_BRG/PNG/08_HSV_ColorCircle_16.png) |
| ![img41](images/Photo/03_Color_Gradients_Photo.png)   | ![img42](images/Screenshots/colors_saved_as_RGB/PNG/03_Color_Gradients_16.png) | ![img43](images/Screenshots/colors_swapped_RGB_to_BRG/PNG/03_Color_Gradients_16.png) |
| ![img51](images/Photo/11_Mandelbrot_Photo.png) | ![img52](images/Screenshots/colors_saved_as_RGB/PNG/11_Mandelbrot_16.png) | ![img52](images/Screenshots/colors_swapped_RGB_to_BRG/PNG/11_Mandelbrot_16.png) |

*Does anyone have an explanation for this unexpected effect?*

In the meantime I have tried all possible color swaps with XnView and found that obviously a conversion from RGB to BRG produces the correct colors. However, saving in this format is not possible with LovyanGFX.

Manual conversion with XnView is necessary because LovyanGFX only allows RGB565 or BGR565 to be saved.


As a little bonus, I let the RGB LEDs flash alternately at second intervals, 🔴red, 🟢green, 🔵blue, ... This flashing runs as separate task, independently of the graphics routines running in the main loop.
