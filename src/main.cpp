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
int8_t volume = 0; // 0-100%
unsigned long beepTime = 0;
int beepDuration = 1000;
int soundFreq = 700;
int soundFreqInc = 100; // Per 1 m/s
float climbThr = 0.1;
float sinkThr = -2.4;
void UpdateSound();
void PlaySound(unsigned long frequency, unsigned long length = 0,
               uint8_t background = false, uint8_t tVolume = 10);

// Screen
char buf[20];
#define BACKLIGHT_PIN PIN_A3
ST7567_FB lcd(7, 8, 6); // dc, rst, cs.
const int8_t fps = 2;   // 2Hz
void UpdateMainScreen();

// Settings
int8_t stateSettings = 0;
const char *textSettings[] = {"SETTINGS", "Volume", "Altitude", "Pressure MSL",
                              "Alpha", "Climb Threshold", "Sink Threshold",
                              "Contrast", "Battery", "Backlight", "About", "Reset"};
void Settings();
void UpdateSettingsScreen();
int16_t value = 0;
void ChangeVolume();
void DisplayVolume();

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
    lcd.setContrast(27);
    lcd.setRotation(4);
    lcd.cls();
    lcd.setFont(c64);
    lcd.printStr(ALIGN_CENTER, 25, "vario-black");
    lcd.display();
    Delay(1000);

    // Settings
    if (EEPROM.read(0) == 255)
    {
        EEPROM.write(0, 0);  // eeprom
        EEPROM.write(1, 1);  // alpha
        EEPROM.write(2, 2);  // climbthr*10
        EEPROM.write(3, 30); // -1*sinkthr*10
        EEPROM.write(4, 70); // soundfreq/10
        EEPROM.write(5, 10); // soundfreqinc
        EEPROM.write(6, 80); // volume %
        lcd.printStr(ALIGN_CENTER, 40, "eeprom set!");
        UpdatePot(100); // pot.
        Delay(5000);
    }

    // Read EEPROM
    volume = EEPROM.read(6);

    // Sensor [Pressure rate: (freq / 2). Max 50Hz when the main loop freq is 100Hz and above]
    if (baro.Init() == false)
    {
        // Serial.println(F("sensor error"));
        lcd.printStr(ALIGN_CENTER, 40, "sensor error!");
        lcd.display();
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
            PlaySound(360 + int(v * 20.0f), 0, true, 5); // Sink volume: 50% of the climb volume.
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
        // Serial.println(F("Sensor failure")); // TODO
        // stateScreen = 3; // TODO
    }

    // lcd.printStr(ALIGN_CENTER, 0, "hi ========== 845");
    // char buf[6];
    snprintf(buf, 6, "%d", (int16_t)baro.GetX() + 143);
    lcd.setFont(Arial18x23);
    // lcd.setFontMinWd(18);
    lcd.printStr(20, 5, buf); // when 4 digits?
    int8_t k = 1;
    if (baro.GetV() < 0)
    {
        snprintf(buf, 6, "%s", "-");
        lcd.printStr(10, 40, buf);
        k = -1;
    }
    snprintf(buf, 6, "%d.%d ", int8_t(baro.GetV() * k), int8_t(baro.GetV() * 10 * k) % 10); // when -10.0?
    lcd.printStr(20, 37, buf);

    // lcd.setFont(c64);
    // snprintf(buf, 6, "%dC", int8_t(baro.GetT())); // add deg.
    // lcd.printStr(50, 0, buf);

    // snprintf(buf, 6, "%d", batteryLevel);
    // lcd.printStr(110, 0, buf);
    // lcd.printStr(120, 0, "%");

    // lcd.drawLineHfast(40, 120, 10, 1); // 30byte

    // lcd.printStr(80, 0, "10%"); // sound

    // lcd.printStr(80, 10, buf);
    // lcd.drawRectD(0, 0, 128, 64, 1);
    // lcd.drawRect(18, 20, 127 - 18 * 2, 63 - 20 * 2, 1);

    lcd.display();
    // lcd.displayInvert(true);
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
            // turning off...? yes/no
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
        else if (IsButtonPressed(BUTTON_DOWN) && stateSettings < 11)
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
                DisplayVolume();
                ChangeVolume();
            }
            else if (stateSettings == 2)
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

void ChangeVolume()
{
    while (IsButtonPressed(BUTTON_BACK) == false)
    {
        if (IsButtonPressed(BUTTON_UP) && value < 100)
        {
            value += 5;
            DisplayVolume();
            Delay(200);
        }
        else if (IsButtonPressed(BUTTON_DOWN) && value > 0)
        {
            value -= 5;
            DisplayVolume();
            Delay(200);
        }
        else if (IsButtonPressed(BUTTON_OK))
        {
            volume = value;
            UpdatePot(volume);
            EEPROM.write(6, volume);
            Delay(500);
        }
    }
}

void DisplayVolume()
{
    lcd.fillRect(45, 44, 50, 7, 0);
    lcd.display();
    snprintf(buf, 20, "%s %d", "%", value);
    lcd.printStr(45, 44, buf);
    lcd.display();
    UpdatePot(value);
    PlaySound(700, 100);
    UpdatePot(volume);
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