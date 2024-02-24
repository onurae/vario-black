/*******************************************************************************************
 *                                                                                         *
 *    Barometric Pressure Sensor (MS5611)                                                  *
 *                                                                                         *
 *    Copyright (c) 2024 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#ifndef BARO_HPP
#define BARO_HPP

#include <Arduino.h>
#include <Wire.h>
#include "util.hpp"

#define ADDRESS_MS5611 0x77 // CSB: Low

class Baro
{
private:
    uint16_t cal[7];                  // Calibration data
    uint32_t dpt[2];                  // Digital pressure & temperature value
    uint8_t addDpt[2] = {0x48, 0x58}; // OCR: 4096. Conversion time: 9.04 [ms] max.
    int64_t tDiff;                    // Difference between actual and reference temperature
    int32_t tAct;                     // Actual temperature
    int64_t tOff;                     // Offset at actual temperature
    int64_t tSens;                    // Sensitivity at actual temperature
    int32_t tCompPres;                // Temperature compensated pressure
    int64_t tRef;                     // Reference temperature
    int64_t tOff1;
    int64_t tSens1;
    int32_t tAct2;
    int64_t tOff2;
    int64_t tSens2;
    bool SendConvCmdPres();
    bool SendConvCmdTemp();
    bool ReadPressure();
    bool ReadTemperature();
    uint32_t lastConv;
    bool ReadPresTemp(); // max 50Hz.
    void Calculate();
    float temperature = 0; // [°C]
    float pressure = 0;    // [mbar]
    float qnh = 1013.25;   // Mean sea level pressure [mbar]
    float tsl = 25.0;      // Temperature sea level [°C]
    float alt = 0;         // Altitude sea level [m]
    bool state = false;    // false: Pres read, temp cmd. true: Pres cmd, temp read.
    bool failure = false;  // Failure flag

    // Filter
    void ApplyFilter(float dt);
    float xk = 0;       // Altitude [m]
    float xk1 = 0;      // Previous altitude [m]
    float vk = 0;       // Vertical speed [m/s]
    float vk1 = 0;      // Previous vertical speed [m/s]
    float alpha = 0.30; // Alpha
public:
    Baro() = default;
    virtual ~Baro() = default;
    bool Init();
    void Update(float dt);
    bool GetState() { return state; }
    bool CheckFailure() { return failure; }
    float GetAlt() { return alt; }
    float GetX() { return xk; }
    float GetV() { return vk; }
    float GetT() { return temperature; }
    float GetAlpha() { return alpha; }
    void SetAlpha(float value) { alpha = value; };
    void InitFilter(float altitude);
    void SetAltitude(float altitude);
};

#endif /* BARO_HPP */