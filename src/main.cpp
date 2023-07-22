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

// Buttons
#define BUTTON_OK PIN_A0
#define BUTTON_BACK 5
#define BUTTON_UP 3
#define BUTTON_DOWN 4

// Backlight
#define BACKLIGHT_PIN PIN_A3

// Sound
int8_t volume = 100; // 0-100%
unsigned long beepTime = 0;
int beepDuration = 1000;
int soundFreq = 700;
int soundFreqInc = 100; // Per 1 m/s
float climbThr = 0.1;
float sinkThr = -2.4;
void UpdateSound();

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

// Battery
#define PIN_BAT PIN_A2
int batteryLevel = 0; // [%]
float vfp = 1.25f;
const float gamma = 0.002f;
void UpdateBattery();

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

    // Digital Pot.
    pinMode(POT_CS, OUTPUT);

    // Backlight.
    pinMode(BACKLIGHT_PIN, OUTPUT);

    // Screen
    lcd.init();
    lcd.setContrast(27);
    lcd.setRotation(4);
    lcd.cls();
    lcd.setFont(c64);
    lcd.printStr(ALIGN_CENTER, 25, "vario-black"); // TODO logo.
    lcd.display();
    Delay(1000);

    // TODO Set settings.
    // DigitalPotWrite(100); // Set volume. No need. it is saved on the chip.
    digitalWrite(BACKLIGHT_PIN, LOW); // Turn backlight off.

    // Sensor [Pressure rate: (freq / 2). Max 50Hz when the main loop freq is 100Hz and above]
    if (baro.Init() == false)
    {
        Serial.println(F("Sensor error"));
        LoopForever();
    }

    // Battery
    for (int i = 0; i < 5000; i++) // ~500ms.
    {
        UpdateBattery();
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
                /*
                Serial.print(baro.GetAlt());
                Serial.print(F("   "));
                Serial.print(baro.GetX());
                Serial.print(F("   "));
                Serial.println(baro.GetV());
                */
                // Serial.print(F("   "));
                // CalculateAverageVario(baro.GetV());
                // Serial.println(vsAverage);
            }
        }
        else
        {
            Serial.println(F("Sensor failure")); // TODO birden fazla gelirse ekrana yazdir.
        }
    }

    // Sound
    UpdateSound();

    // Screen
    counterLcd += 1;
    if (counterLcd >= (1000 / fps / period))
    {
        counterLcd = 0;
        UpdateLcd();
    }

    // Battery
    UpdateBattery();

    // Power off
    if (IsButtonPressed(BUTTON_BACK) == true)
    {
        toneAC(1000, 10, 200, true);
        lcd.cls();
        lcd.display();
        Delay(100);
        pinMode(BUTTON_OK, INPUT);
    }

    // Backlight Test
    if (IsButtonPressed(BUTTON_UP) == true)
    {
        digitalWrite(BACKLIGHT_PIN, LOW);
        DigitalPotWrite(100);
    }
    if (IsButtonPressed(BUTTON_DOWN) == true)
    {
        digitalWrite(BACKLIGHT_PIN, HIGH);
        DigitalPotWrite(250); // Max 250 for 10mA!
    }
}

void UpdateSound()
{
    if (int(millis() - beepTime) >= 2 * beepDuration)
    {
        float vario = baro.GetV();
        float v = int(vario * 10) / 10.0f;
        beepDuration = 50;
        if (int(vario * 10) >= int(climbThr * 10))
        {
            if (int(vario * 10) < 37)
            {
                beepDuration = int(((-0.0002f * v * v * v * v + 0.0003f * v * v * v + 0.0194f * v * v - 0.145f * v + 0.392f) * 1000.0f) / 50.0f) * 50;
                beepTime = millis();
            }
            toneAC(soundFreq + soundFreqInc * (v - 0.1f), 10, beepDuration, true);
        }
        else if (int(vario * 10) < int(sinkThr * 10))
        {
            toneAC(360 + int(v * 20.0f), 5, 0, true); // Sink volume: 50% of the climb volume.
        }
        else
        {
            toneAC(0);
        }
    }
}

void UpdateBattery()
{
    int value = analogRead(PIN_BAT);
    float voltage = value * (3.3f / 1024.0f) * 0.5f; // 1 battery.
    // Filtered voltage
    float vf = (1.0f - gamma) * vfp + gamma * voltage;
    vfp = vf;
    // Assume linear discharge curve.
    batteryLevel = (100.0f * (vf - 1.0f) / (1.5f - 1.0f)); // Max: 1.5V, Min: 1.0V
    if (batteryLevel >= 100)
    {
        batteryLevel = 100;
    }
    else if (batteryLevel <= 0)
    {
        batteryLevel = 0;
    }
}

void UpdateLcd()
{
    lcd.cls();
    lcd.setFont(c64);
    i += 1;
    if (i > 30)
    {
        i = 0;
    }
    lcd.printStr(i + 5, 5, "X");

    // lcd.printStr(ALIGN_CENTER, 0, "hi ========== 845");
    char buf[6];
    snprintf(buf, 6, "%d", (int16_t)baro.GetX());
    lcd.setFont(Arial16x21);
    lcd.printStr(44, 15, buf); // when 4 digits?
    int8_t k = 1;
    if (baro.GetV() < 0)
    {
        snprintf(buf, 6, "%s", "-");
        lcd.printStr(30, 40, buf);
        k = -1;
    }
    snprintf(buf, 6, "%d.%d ", int8_t(baro.GetV() * k), int8_t(baro.GetV() * 10 * k) % 10); // when -10.0?
    lcd.printStr(44, 42, buf);

    lcd.setFont(c64);
    snprintf(buf, 6, "%dC", int8_t(baro.GetT())); // add deg.
    lcd.printStr(50, 0, buf);

    snprintf(buf, 6, "%d", batteryLevel);
    lcd.printStr(110, 0, buf);
    lcd.printStr(120, 0, "%");

    lcd.drawLineHfast(40, 120, 10, 1); // 30byte

    lcd.printStr(80, 0, "10%"); // sound

    // lcd.printStr(80, 10, buf);
    // lcd.drawRectD(0, 0, 128, 64, 1);
    // lcd.drawRect(18, 20, 127 - 18 * 2, 63 - 20 * 2, 1);

    lcd.display();
    // lcd.displayInvert(true);
}

/*
// Average vario, only used for gain in thermal function.
int8_t arr[freq * 15] = {0}; // Max. 30 seconds average: (freq/2)*30
int16_t vsIndex = 0;
long vsSum = 0;
float vsAverage = 0;
int vsAverageTime = 10;
void CalculateAverageVario(float vk)
{
    vsSum -= arr[vsIndex];
    arr[vsIndex] = int8_t(vk * 10.0f); // [-12.8, 12.7]
    vsSum += arr[vsIndex];
    vsIndex += 1;
    if (vsIndex >= int16_t(vsAverageTime * freq * 0.5f))
    {
        vsIndex = 0;
    }
    vsAverage = vsSum / 10.0f / (vsAverageTime * freq * 0.5f);
}
*/