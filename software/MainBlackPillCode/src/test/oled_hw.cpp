/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

This example is for a 128x32 size display using I2C

if you get the error:Adafruit._GFX.h not found, download Adafruit-GFX Library
https://github.com/adafruit/Adafruit-GFX-Library


Purchase this OLED module from Amazon: https://amzn.to/36zFvTb

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution

* Watch the video for this code to learn it fully.
 * Watch the video here: https://youtu.be/RjyulqVsz2o
* this code is offered "as is" without any warranty.
*  Updated by Ahmad Shamshiri For Robojax.com video tutorial
* on March 18, 2018 at 10:21 at Ajax, Ontario, Canada
* Please view other Robojax codes and videos at http://robojax.com/learn/arduino
* if you are sharing this code, you must keep this copyright note.
*
*********************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_I2C_ADDR 0x3C
/*
 * PIN connection:
 * pin connection see: https://www.arduino.cc/en/Reference/Wire
 * for UNO: SDA to A4, SCL to A5
 * for Mega2560: SDA to 20, SCL to 21
 * for Leonardo: SDA to 2, SCL to 3
 * for Due: SDA to 20, SCL to 21
 * VCC to 5V
 * GND to GND :-)
 */

// guarda qui: https://community.platformio.org/t/stm32f411-based-custom-pcb-i2c-debugging/48614/2
#ifdef BLACKPILL_F411CE
  #define PIN_WIRE_SDA PB7 
  #define PIN_WIRE_SCL PB6
#endif 


#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
//TODO: Adafruit considera deprecato il costruttore, convertire in nuovo
Adafruit_SSD1306 display(OLED_RESET);


#if (SSD1306_LCDHEIGHT != 32)
#error ("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()
{
  Serial.begin(115200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR))
  {
    while (1)
    {
      Serial.println(F("SSD1306 allocation failed"));
      ; // Don't proceed, loop forever
    }
  }
  display.setTextSize(2);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
}

void loop()
{

  Serial.println("OLED HW Test:ora scrivo Ciao mondo");
  display.clearDisplay();
  display.setCursor(0, 0); // Start at top-left corner

  display.println("Ciao mondo");
  display.println(F("1234567890"));
 
  display.display();
  delay(2000);
}
