/*******************************************************************************************
 *                                                                                         *
 *    Vario-Black                                                                          *
 *                                                                                         *
 *    Copyright (c) 2023 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#include "ST7567_FB.h"
#include "toneAC.h"
#include "baro.hpp"
#include "font.hpp"
#include "c64enh_font.h"

// Buttons
#define BUTTON_OK PIN_A0
#define BUTTON_BACK PIN_A1
#define BUTTON_UP PIN_A2
#define BUTTON_DOWN PIN_A3

// Screen
ST7567_FB lcd(7, 8, 6); // dc, rst, cs.
const int8_t fps = 2;   // 2Hz
int8_t counterLcd = 0;
int8_t iRefresh = 0;
int8_t i = 0;
void UpdateLcd();

// Sensor
Baro baro;
const int8_t freq = 10; // 10Hz
int8_t counterBaro = 0;

// Main loop
const int8_t period = 50; // [ms]
unsigned long start;
unsigned long end;
int8_t elapsed;

void setup()
{
    Serial.begin(115200);
    Serial.println("vario-black");
    toneAC(1000, 10, 200, true);

    // Buttons
    pinMode(BUTTON_OK, INPUT_PULLUP);
    pinMode(BUTTON_BACK, INPUT_PULLUP);
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);

    // Screen
    lcd.init();
    lcd.setContrast(0);
    lcd.setRotation(4);
    lcd.cls();
    lcd.display();

    // Sensor [Pressure rate: (freq / 2). Max 50Hz when the main loop freq is 100Hz and above]
    if (baro.Init() == false)
    {
        Serial.println(F("Sensor error"));
        LoopForever();
    }

    // Main loop
    start = millis();
}

void loop()
{
    // Period
    end = millis();
    elapsed = end - start;
    // Serial.println(elapsed);
    if (elapsed < period)
    {
        Delay(period - elapsed);
    }
    start = millis();

    // Sensor
    counterBaro += 1;
    if (counterBaro >= (1000 / freq / period))
    {
        counterBaro = 0;
        baro.Update(1.0f / freq);
        if (baro.CheckFailure() == false)
        {
            // Print baro values only when the state is true.
            if (baro.GetState() == true)
            {
                Serial.print(baro.GetAlt());
                Serial.print(F("   "));
                Serial.print(baro.GetX());
                Serial.print(F("   "));
                Serial.println(baro.GetV());
                // Serial.print(F("   "));
                // CalculateAverageVario(baro.GetV());
                // Serial.println(vsAverage);
            }
        }
        else
        {
            Serial.println(F("Sensor failure"));
        }
    }

    // Screen
    counterLcd += 1;
    if (counterLcd >= (1000 / fps / period))
    {
        counterLcd = 0;
        UpdateLcd();
    }

    // Power off
    if (IsButtonPressed(BUTTON_BACK) == true)
    {
        toneAC(1000, 10, 200, true);
        lcd.cls();
        lcd.display();
        Delay(100);
        pinMode(BUTTON_OK, INPUT);
    }
}

void UpdateLcd()
{
    lcd.cls();
    lcd.setFont(c64enh);
    i += 1;
    if (i > 30)
    {
        i = 0;
    }
    lcd.printStr(i + 5, 5, "X");

    //lcd.printStr(ALIGN_CENTER, 50, "Hello World!");
    char buf[6];
    snprintf(buf, 6, "%d", (int16_t)baro.GetX());
    lcd.setFont(Arial16x21);
    lcd.printStr(44, 4, buf);
    int8_t k = 1;
    if (baro.GetV() < 0)
    {
        snprintf(buf, 6, "%s", "-");
        lcd.printStr(30, 40, buf);
        k = -1;
    }
    snprintf(buf, 6, "%d.%d ", int8_t(baro.GetV() * k), int8_t(baro.GetV() * 10 * k) % 10);
    lcd.printStr(44, 40, buf);
    // lcd.printStr(80, 10, buf);
    // lcd.drawRectD(0, 0, 128, 64, 1);
    // lcd.drawRect(18, 20, 127 - 18 * 2, 63 - 20 * 2, 1);

    lcd.display();
    // lcd.displayInvert(true);
}