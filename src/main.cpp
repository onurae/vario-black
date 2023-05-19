#include <Arduino.h>
#include "toneAC.h"
#include "ST7567_FB.h"

// Buttons
#define BUTTON_OK PIN_A0
#define BUTTON_BACK PIN_A1
#define BUTTON_UP PIN_A2
#define BUTTON_DOWN PIN_A3

// LCD
ST7567_FB lcd(7, 8, 6);

// Main loop
unsigned long start;
unsigned long end;
int8_t elapsed;

void Delay(unsigned long interval)
{
    unsigned long previous = millis();
    unsigned long current = previous;
    while (current - previous < interval)
    {
        current = millis();
    }
}

void setup()
{
    Delay(500);
    Serial.begin(115200);
    Serial.println("vario-black");
    toneAC(1000, 10, 200, true);

    // Buttons
    pinMode(BUTTON_OK, INPUT_PULLUP);
    pinMode(BUTTON_BACK, INPUT_PULLUP);
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);

    // LCD
    lcd.init();
    lcd.setContrast(0);
    lcd.cls();
    lcd.display();

    // Main loop
    start = millis();

    lcd.cls();
    lcd.drawRectD(0, 0, SCR_WD, SCR_HT, 1);
    int x = 16, y = 10;
    lcd.drawRect(x + 8, y - 5, 20, 20, 1);
    lcd.fillRect(x + 8 + 30, y - 5, 20, 20, 1);
    lcd.fillRectD(x + 8 + 60, y - 5, 20, 20, 1);
    lcd.drawCircle(x + 5 + 12, 48, y, 1);
    lcd.fillCircle(x + 5 + 30 + 12, y + 36, 12, 1);
    lcd.fillCircleD(x + 5 + 60 + 12, y + 36, 12, 1);
    lcd.display();
}

void loop()
{
    // Period
    end = millis();
    elapsed = end - start;
    Serial.println(elapsed);
    int8_t period = 100;
    if (elapsed < period)
    {
        Delay(period - elapsed);
    }
    start = millis();

    // Power off
    if (digitalRead(BUTTON_BACK) == 0)
    {
        toneAC(1000, 10, 200, true);
        Delay(500);
        pinMode(BUTTON_OK, INPUT);
    }
}