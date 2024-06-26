/*******************************************************************************************
 *                                                                                         *
 *    Barometric Pressure Sensor (MS5611)                                                  *
 *                                                                                         *
 *    Copyright (c) 2024 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#include "baro.hpp"

bool Baro::Init()
{
    Wire.begin();
    Wire.setWireTimeout(25000, false);
    Wire.beginTransmission(ADDRESS_MS5611);
    Wire.write(0x1E); // Reset
    if (Wire.endTransmission())
    {
        return false;
    }
    Delay(10);
    for (int i = 0; i < 6; i++)
    {
        Wire.beginTransmission(ADDRESS_MS5611);
        Wire.write(0xA2 + (i * 2));
        Wire.endTransmission();

        Wire.beginTransmission(ADDRESS_MS5611);
        if (Wire.requestFrom(ADDRESS_MS5611, 2) == 2)
        {
            cal[i] = ((uint16_t)Wire.read()) << 8 | (uint16_t)Wire.read();
        }
    }
    // printf(" C1: %d\n C2: %d\n C3: %d\n C4: %d\n C5: %d\n C6: %d\n", cal[0], cal[1], cal[2], cal[3], cal[4], cal[5]);
    tRef = (int64_t)cal[4] << 8;
    tOff1 = (int64_t)cal[1] << 16;
    tSens1 = (int64_t)cal[0] << 15;

    if (SendConvCmdTemp() == false) // Send temperature command
    {
        return false;
    }
    Delay(10);
    if (ReadTemperature() == false) // Read digital temperature value
    {
        return false;
    }
    if (SendConvCmdPres() == false) // Send pressure command
    {
        return false;
    }
    lastConv = millis();
    Delay(10);
    if (ReadPresTemp() == false) // Read digital pressure value, send temperature command.
    {
        return false;
    }
    Calculate();     // Calculate pressure, temperature and altitude.
    InitFilter(alt); // Initial conditions for filter.
    return true;
}

void Baro::Update(float dt)
{
    if (ReadPresTemp() == true)
    {
        if (state == true)
        {
            Calculate();
            ApplyFilter(dt * 2.0f);
        }
        failure = false;
    }
    else
    {
        xk = 0;
        vk = 0;
        failure = true;
    }
}

bool Baro::SendConvCmdPres()
{
    Wire.beginTransmission(ADDRESS_MS5611);
    Wire.write(addDpt[0]);
    if (Wire.endTransmission())
    {
        return false;
    }
    return true;
}

bool Baro::SendConvCmdTemp()
{
    Wire.beginTransmission(ADDRESS_MS5611);
    Wire.write(addDpt[1]);
    if (Wire.endTransmission())
    {
        return false;
    }
    return true;
}

bool Baro::ReadPressure()
{
    Wire.beginTransmission(ADDRESS_MS5611);
    Wire.write(0x00);
    if (Wire.endTransmission())
    {
        return false;
    }
    Wire.beginTransmission(ADDRESS_MS5611);
    if (Wire.requestFrom(ADDRESS_MS5611, 3) == 3)
    {
        dpt[0] = ((uint32_t)Wire.read() << 16) | ((uint32_t)Wire.read() << 8) | (uint32_t)Wire.read();
        if (dpt[0] == 0) // if loop is fast, it returns 0.
        {
            return false;
        }
        return true;
    }
    return false;
}

bool Baro::ReadTemperature()
{
    Wire.beginTransmission(ADDRESS_MS5611);
    Wire.write(0x00);
    if (Wire.endTransmission())
    {
        return false;
    }
    Wire.beginTransmission(ADDRESS_MS5611);
    if (Wire.requestFrom(ADDRESS_MS5611, 3) == 3)
    {
        dpt[1] = ((uint32_t)Wire.read() << 16) | ((uint32_t)Wire.read() << 8) | (uint32_t)Wire.read();
        if (dpt[1] == 0) // if loop is fast, it returns 0.
        {
            return false;
        }
        return true;
    }
    return false;
}

bool Baro::ReadPresTemp()
{
    uint32_t current = millis();
    if ((current - lastConv) < 10)
    {
        return false;
    }
    lastConv = current;

    // If the sample rate is 100Hz, pressure & temperature refresh rate would be 50Hz.
    if (state == false)
    {
        bool pState = ReadPressure();
        bool tState = SendConvCmdTemp();
        if (pState && tState)
        {
            state = true;
            return true;
        }
    }
    else
    {
        bool tState = ReadTemperature();
        bool pState = SendConvCmdPres();
        if (tState && pState)
        {
            state = false;
            return true;
        }
    }
    return false;
}

void Baro::Calculate()
{
    tDiff = (int64_t)dpt[1] - tRef;
    tAct = 2000 + ((tDiff * cal[5]) >> 23);
    tOff = tOff1 + ((tDiff * cal[3]) >> 7);
    tSens = tSens1 + ((tDiff * cal[2]) >> 8);

    if (tAct < 2000) // Temperature < 20°C
    {
        tAct2 = (tDiff * tDiff) >> 31;
        int64_t x = tAct - 2000;
        x = 5 * x * x;
        tOff2 = x >> 1;
        tSens2 = x >> 2;
        if (tAct < -1500) // Temperature < -15°C
        {
            x = tAct + 1500;
            x = x * x;
            tOff2 += 7 * x;
            tSens2 += ((11 * x) >> 2);
        }
        tAct -= tAct2;
        tOff -= tOff2;
        tSens -= tSens2;
    }

    temperature = tAct / 100.0f;
    tCompPres = (((((int64_t)dpt[0] * tSens) >> 21) - tOff) >> 15);
    pressure = tCompPres / 100.0f;
    alt = (((tsl + 273.15f) / -0.0065f) * (pow(pressure / qnh, 0.1902632f) - 1.0f));
}

void Baro::ApplyFilter(float dt)
{
    float rk;
    xk = xk1 + (vk1 * dt);
    vk = vk1;
    rk = alt - xk;
    xk = xk + alpha * rk;
    vk = vk + (2.0f * (2.0f - alpha) - 4.0f * (sqrt(1.0f - alpha))) * rk / dt;

    xk1 = xk;
    vk1 = vk;
    return;

    // For vario sine wave test.
    static float t = 0;
    t += dt;
    vk = 5.0f * sin(0.025f * t);
}

void Baro::InitFilter(float altitude)
{
    xk1 = altitude;
    vk1 = 0;
    xk = xk1;
    vk = vk1;
}

void Baro::SetAltitude(float altitude)
{
    qnh = (pressure / (pow(((altitude / ((tsl + 273.15) / (-0.0065))) + 1), 1 / 0.1902632)));
    InitFilter(altitude);
}