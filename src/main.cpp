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
#include <EEPROM.h>
#include <SPI.h>

// Buttons
#define BUTTON_OK PIN_A0
#define BUTTON_BACK 5
#define BUTTON_UP 3
#define BUTTON_DOWN 4
void DetectLongPress();

// Pot
#define POT_ADDRESS 0x11
#define POT_CS 7
void UpdatePot(int16_t volume);

// Sound
int8_t volume = 100; // 0-100%
unsigned long beepTime = 0;
int beepDuration = 1000;
int soundFreq = 700;
int soundFreqInc = 100; // Per 1 m/s
float climbThr = 0.1;
float sinkThr = -2.4;
void UpdateSound();
void PlaySound(unsigned long frequency, unsigned long length = 0, uint8_t background = false, uint8_t tVolume = 10);

// Screen
char buf[20];
#define BACKLIGHT_PIN PIN_A3
ST7567_FB lcd(7, 8, 6); // dc, rst, cs.
int8_t contrast = 31;
const int8_t fps = 2; // 2Hz
void UpdateMainScreen();

// Settings
int8_t stateSettings = 0;
const char *textSettings[] = {"SETTINGS", "Volume", "Altitude", "Climb Threshold", "Sink Threshold", "Alpha", "Contrast", "Reset", "About"};
void Settings();
int16_t value = 0;

// Sensor
Baro baro;
const int8_t freq = 10; // 10Hz
void UpdateSensor();

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
    // Serial.begin(115200);
    // Serial.println("vario-black");

    // Power
    PlaySound(1000, 200);

    // Buttons
    pinMode(BUTTON_OK, INPUT_PULLUP);
    pinMode(BUTTON_BACK, INPUT_PULLUP);
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);

    // Digital Pot.
    pinMode(POT_CS, OUTPUT);

    // Screen
    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, LOW);
    lcd.init();
    lcd.setContrast(contrast);
    lcd.setRotation(4);
    lcd.cls();
    lcd.setFont(c64);
    snprintf(buf, 20, "vario-black");
    lcd.printStr(25, 25, buf);
    lcd.display();
    Delay(1000);

    // Settings
    if (EEPROM.read(0) == 255)
    {
        EEPROM.write(0, 0);  // eeprom
        EEPROM.write(1, 80); // volume %
        EEPROM.write(3, 1);  // climbthr*10
        EEPROM.write(4, 24); // -1*sinkthr*10
        EEPROM.write(5, 30); // alpha*100
        EEPROM.write(6, 31); // contrast
        snprintf(buf, 20, "eeprom set!");
        lcd.printStr(25, 40, buf);
        lcd.display();
        Delay(5000);
    }
    volume = EEPROM.read(1);
    UpdatePot(volume);
    climbThr = EEPROM.read(3) / 10.0f;
    sinkThr = EEPROM.read(4) / -10.0f;
    baro.SetAlpha(EEPROM.read(5) / 100.0f);
    contrast = EEPROM.read(6);
    lcd.setContrast(contrast);

    // Sensor [Pressure rate: (freq / 2). Max 50Hz when the main loop freq is 100Hz and above]
    if (baro.Init() == false)
    {
        // Serial.println(F("sensor error"));
        snprintf(buf, 20, "sensor error!");
        lcd.printStr(25, 40, buf);
        lcd.display();
        LoopForever();
    }

    // Battery
    for (int i = 0; i < 5000; i++) // ~500ms.
    {
        UpdateBattery();
    }
    // TODO show battery level...

    // Main loop
    start = millis();
}

void loop()
{
    end = millis();
    elapsed = end - start;
    if (elapsed < period)
    {
        Delay(period - elapsed);
    }
    else
    {
        // Serial.println(elapsed);
    }
    start = millis();

    UpdateSensor();
    UpdateSound();
    UpdateBattery();
    UpdateMainScreen();
    DetectLongPress();
}

void UpdateSensor()
{
    static int8_t counterSensor = 0;
    counterSensor += 1;
    if (counterSensor >= (1000 / freq / period))
    {
        counterSensor = 0;
        baro.Update(1.0f / freq);
    }
}

void UpdatePot(int16_t volume)
{
    if (volume >= 0 && volume <= 100)
    {
        digitalWrite(POT_CS, LOW);
        SPI.transfer(POT_ADDRESS);
        SPI.transfer(volume * 2.5f); // Max:250, 10mA.
        digitalWrite(POT_CS, HIGH);
    }
}

void PlaySound(unsigned long frequency, unsigned long length, uint8_t background, uint8_t tVolume)
{
    toneAC(frequency, volume == 0 ? 0 : tVolume, length, background);
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
            PlaySound(soundFreq + soundFreqInc * (v - 0.1f), beepDuration, true);
        }
        else if (int(vario * 10) < int(sinkThr * 10))
        {
            PlaySound(360 + int(v * 20.0f), 0, true, 5); // Sink volume: 50% of the climb volume. // TODO maybe %100, maybe smooth? vario instead v? oscilation?
        }
        else
        {
            PlaySound(0);
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

void UpdateMainScreen()
{
    static int8_t counterScreen = 0;
    counterScreen += 1;
    if (counterScreen < (1000 / fps / period))
    {
        return;
    }
    counterScreen = 0;
    lcd.cls();
    if (baro.CheckFailure() == true)
    {
        lcd.setFont(c64);
        snprintf(buf, 20, "sensor error!");
        lcd.printStr(20, 23, buf);
        lcd.display();
        return;
    }

    lcd.setFont(Icons21x21);
    lcd.printChar(5, 15, 32);
    lcd.printChar(5, 43, 33);
    lcd.printChar(53, 0, 34);
    lcd.printChar(91, 0, 35);

    lcd.setFont(c64);
    snprintf(buf, 6, "%d C'", int8_t(baro.GetT()));
    lcd.printStr(5, 0, buf);
    snprintf(buf, 4, "%d", volume);
    lcd.printStr(65, 0, buf);
    snprintf(buf, 4, "%d", batteryLevel);
    lcd.printStr(106, 0, buf);
    lcd.drawLineHfastD(0, 127, 9, 1);
    snprintf(buf, 2, "m");
    lcd.printStr(106, 29, buf);
    snprintf(buf, 4, "m/s");
    lcd.printStr(106, 56, buf);

    lcd.setFont(Arial16x21);
    snprintf(buf, 6, "%d", int16_t(baro.GetX()));
    lcd.printStr(39, 15, buf);
    int16_t k = 1;
    if (baro.GetV() < 0)
    {
        snprintf(buf, 2, "%s", "-");
        lcd.printStr(36, 40, buf);
        k = -1;
    }
    snprintf(buf, 5, "%d.%d ", int16_t(baro.GetV() * k), int16_t(baro.GetV() * 10 * k) % 10);
    lcd.printStr(50, 42, buf);
    lcd.display();
}

void DetectLongPress()
{
    static int8_t counterButton = 0;
    if (IsButtonPressed(BUTTON_BACK)) // Power off.
    {
        counterButton = counterButton + 1;
        if (counterButton > (1000 / period) * 2) // 2 seconds.
        {
            counterButton = 0;
            PlaySound(1000, 200);
            lcd.cls();
            lcd.display();
            Delay(1000);
            pinMode(BUTTON_OK, INPUT);
        }
    }
    else if (IsButtonPressed(BUTTON_UP))
    {
        // digitalWrite(BACKLIGHT_PIN, LOW);
        // DigitalPotWrite(100);
    }
    else if (IsButtonPressed(BUTTON_DOWN))
    {
        // digitalWrite(BACKLIGHT_PIN, HIGH);
        // DigitalPotWrite(250); // Max 250 for 10mA!
    }
    else if (IsButtonPressed(BUTTON_OK))
    {
        counterButton += 1;
        if (counterButton > (1000 / period) * 2) // 2 seconds.
        {
            counterButton = 0;
            Settings();
        }
    }
    else
    {
        counterButton = 0;
    }
}

void UpdateSettingsScreen()
{
    lcd.cls();
    lcd.setFont(c64);
    snprintf(buf, 20, "%s", textSettings[0]);
    lcd.printStr(38, 5, buf);
    lcd.drawLineHfast(0, 127, 15, 1);
    snprintf(buf, 20, "%d. %s", stateSettings, textSettings[stateSettings]);
    lcd.printStr(5, 20, buf);
    lcd.display();
}

void DisplayEdit()
{
    if (stateSettings == 1)
    {
        snprintf(buf, 20, "%d%s", value, " %");
        UpdatePot(value);
        PlaySound(700, 100, 0, value == 0 ? 0 : 10);
        UpdatePot(volume);
    }
    else if (stateSettings == 2)
    {
        snprintf(buf, 20, "%d%s", value, " m");
    }
    else if (stateSettings == 3)
    {
        snprintf(buf, 20, "%d.%d%s", value / 10, value - (value / 10) * 10, " m/s");
    }
    else if (stateSettings == 4)
    {
        snprintf(buf, 20, "-%d.%d%s", -value / 10, -value - (-value / 10) * 10, " m/s");
    }
    else if (stateSettings == 5)
    {
        snprintf(buf, 20, "0.%d", value);
    }
    else if (stateSettings == 6)
    {
        lcd.setContrast(value);
        snprintf(buf, 20, "%d", value - 31);
    }
    else if (stateSettings == 7)
    {
        value == 0 ? snprintf(buf, 20, "YES") : snprintf(buf, 20, "NO");
    }
    lcd.fillRect(7, 43, 113, 8, 0);
    lcd.display();
    lcd.printStr(ALIGN_CENTER, 43, buf);
    lcd.display();
}

void Save()
{
    if (stateSettings == 1)
    {
        volume = value;
        UpdatePot(volume);
        EEPROM.write(1, volume);
    }
    else if (stateSettings == 2)
    {
        baro.SetAltitude(value);
        // No need to save the qnh, it changes daily.
    }
    else if (stateSettings == 3)
    {
        climbThr = value / 10.0f;
        EEPROM.write(3, climbThr * 10);
    }
    else if (stateSettings == 4)
    {
        sinkThr = value / 10.0f;
        EEPROM.write(4, sinkThr * -10);
    }
    else if (stateSettings == 5)
    {
        baro.SetAlpha(value / 100.0f);
        EEPROM.write(5, value);
    }
    else if (stateSettings == 6)
    {
        contrast = value;
        lcd.setContrast(contrast);
        EEPROM.write(6, value);
    }
    else if (stateSettings == 7)
    {
        if (value == 0)
        {
            EEPROM.write(0, 255);
            PlaySound(1000, 200);
            lcd.cls();
            lcd.display();
            pinMode(BUTTON_OK, INPUT);
            Delay(1000);
        }
    }
    PlaySound(1000, 50);
    Delay(50);
    PlaySound(1000, 50);
}

void DisplayEditIcon()
{
    lcd.fillRect(3, 43, 7, 8, 0);
    lcd.display();
    lcd.printChar(3, 43, 132);
    lcd.display();
}

void DisplaySaveIcon()
{
    lcd.fillRect(3, 43, 7, 8, 0);
    lcd.display();
    lcd.printChar(3, 42, 133);
    lcd.display();
}

void Edit(int16_t min, int16_t max, int16_t inc)
{
    lcd.printChar(3, 32, 128);
    lcd.printChar(3, 54, 129);
    lcd.printChar(118, 32, 130);
    lcd.printChar(118, 54, 131);
    lcd.display();
    Delay(500);
    while (IsButtonPressed(BUTTON_BACK) == false)
    {
        if (IsButtonPressed(BUTTON_UP) && value < max)
        {
            value += inc;
            DisplayEdit();
            DisplayEditIcon();
            Delay(200);
        }
        else if (IsButtonPressed(BUTTON_DOWN) && value > min)
        {
            value -= inc;
            DisplayEdit();
            DisplayEditIcon();
            Delay(200);
        }
        else if (IsButtonPressed(BUTTON_OK))
        {
            Save();
            DisplaySaveIcon();
            Delay(500);
        }
    }
}

void Settings()
{
    stateSettings = 1;
    UpdateSettingsScreen();
    PlaySound(1000, 100);
    Delay(100);
    PlaySound(1000, 100);
    Delay(500);
    while (IsButtonPressed(BUTTON_BACK) == false)
    {
        if (IsButtonPressed(BUTTON_UP) && stateSettings > 1)
        {
            stateSettings--;
            UpdateSettingsScreen();
            Delay(200);
        }
        else if (IsButtonPressed(BUTTON_DOWN) && stateSettings < 9)
        {
            stateSettings++;
            UpdateSettingsScreen();
            Delay(200);
        }
        else if (IsButtonPressed(BUTTON_OK))
        {
            lcd.drawRectD(0, 30, 128, 34, 1);
            if (stateSettings == 1)
            {
                value = volume;
                DisplayEdit();
                Edit(0, 100, 5);
            }
            else if (stateSettings == 2)
            {
                value = baro.GetX();
                DisplayEdit();
                Edit(-1000, 10000, 1);
            }
            else if (stateSettings == 3)
            {
                value = climbThr * 10;
                DisplayEdit();
                Edit(1, 5, 1);
            }
            else if (stateSettings == 4)
            {
                value = sinkThr * 10;
                DisplayEdit();
                Edit(-200, -10, 1);
            }
            else if (stateSettings == 5)
            {
                value = baro.GetAlpha() * 100.0f;
                DisplayEdit();
                Edit(10, 50, 1);
            }
            else if (stateSettings == 6)
            {
                value = contrast;
                DisplayEdit();
                Edit(0, 63, 1);
                lcd.setContrast(contrast);
            }
            else if (stateSettings == 7)
            {
                value = 1;
                DisplayEdit();
                Edit(0, 1, 1);
            }
            else if (stateSettings == 8)
            {
                while (IsButtonPressed(BUTTON_BACK) == false)
                {
                    snprintf(buf, 20, "github.com/onurae");
                    lcd.printStr(5, 33, buf);
                    snprintf(buf, 20, "Designed for METU");
                    lcd.printStr(5, 43, buf);
                    snprintf(buf, 20, "paraglider pilots.");
                    lcd.printStr(5, 53, buf);
                    lcd.display();
                }
            }
            else if (stateSettings == 9)
            {
                while (IsButtonPressed(BUTTON_BACK) == false)
                {
                    lcd.printStr(38, 40, "'()*+,-./:;<=>?");
                    lcd.printStr(38, 50, "[]^_`{|}~");
                    lcd.display();
                }
            }
            UpdateSettingsScreen();
            Delay(500);
        }
    }
}