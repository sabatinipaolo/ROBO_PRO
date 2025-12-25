#include <Arduino.h>
#include "robot.h"
#ifdef HAS_OLED_DISPLAY
    #include <Wire.h>
    #include <Adafruit_SSD1306.h>
    #define SCREEN_WIDTH 128 // OLED display width, in pixels
    #define SCREEN_HEIGHT 32 // OLED display height, in pixels
    #define OLED_I2C_ADDR 0x3C
    #define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

    Adafruit_SSD1306 display(OLED_RESET);
#endif

Robot rob ;

static void ISR_encoder_AD(){
    rob._mot_ant_dx.ISR_encoder();
}
static void ISR_encoder_PD(){
    rob._mot_pos_dx.ISR_encoder();
}
static void ISR_encoder_PS(){
    rob._mot_pos_sx.ISR_encoder();
}
static void ISR_encoder_AS(){
    rob._mot_ant_sx.ISR_encoder();
}

long last_time=0;

void setup(){
    
    Serial.begin(115200);
    
    delay(1000); // Give some time to the Serial Monitor to start
    
    Serial.println("Setup started");
    
    Wire.begin(); // Join I2C bus as master
    Serial.println("I2C bus started");


    #ifdef HAS_OLED_DISPLAY
    Serial.println("Initializing OLED display...");
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR))
    {   
        while (1)
        {   
            Serial.println(F("SSD1306 allocation failed"));
            digitalWrite(LED_BUILTIN,HIGH);
            delay(300);
            digitalWrite(LED_BUILTIN,LOW);
            delay(300);
            digitalWrite(LED_BUILTIN,HIGH);
            delay(300);
            digitalWrite(LED_BUILTIN,LOW);
            delay(1000);
            digitalWrite(LED_BUILTIN,HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN,LOW);
            delay(300);            
        }
    }
    Serial.println("Initializing OLED display...: done");
    display.setTextSize(2);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.clearDisplay();
    display.setCursor(0, 0); // Start at top-left corner

    display.println("ROBOPRO");
    display.display();
    #endif

    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AD1), ISR_encoder_AD, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_PD1), ISR_encoder_PD, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_PS1), ISR_encoder_PS, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_AS, RISING);

    rob._mot_ant_dx.orario(155);
    rob._mot_ant_sx.orario(155);
    rob._mot_pos_sx.orario(155);
    rob._mot_pos_dx.orario(155);
}

void loop(){
    
    delay(200);
    for (int i=0; i<4;i++) rob.motori[i].aggiorna_rpm();
    
    display.clearDisplay();
    display.setCursor(0, 0); 

    
    char str[5];
    dtostrf(rob._mot_ant_sx._rpm, 5, 0, str);
    display.print(str);

    dtostrf(rob._mot_ant_dx._rpm, 5, 0, str);
    display.println(str);

    dtostrf(rob._mot_pos_sx._rpm, 5, 0, str);
    display.print(str);

    dtostrf(rob._mot_pos_dx._rpm, 5, 0, str);
    display.println(str);

    display.display();

}