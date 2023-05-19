/*******************************************************************************************
 *                                                                                         *
 *    Barometric Pressure Sensor (MS5611)                                                  *
 *                                                                                         *
 *    Copyright (c) 2023 Onur AKIN <https://github.com/onurae>                             *
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
    uint16_t cal[7];                    // Calibration data
    uint32_t dpt[2];                    // Digital pressure & temperature value
    uint8_t addDpt[2] = {0x48, 0x58};   // OCR: 4096. Conversion time: 9.04 [ms] max.
    int64_t tDiff;                      // Difference between actual and reference temperature
    int32_t tAct;                       // Actual temperature
    int64_t tOff;                       // Offset at actual temperature
    int64_t tSens;                      // Sensitivity at actual temperature
    int32_t tCompPres;                  // Temperature compensated pressure
    int64_t tRef;                       // Reference temperature
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
    void CalculatePresTempAlt();
    float temperature = 0; // [°C]
    float pressure = 0;    // [mbar]
    float qnh = 1023.00;   // Mean sea level pressure [mbar]
    float tsl = 25.0;      // Temperature sea level [°C]
    float alt = 0;         // Altitude sea level [m]
    bool state = false;    // false: Pres read, temp cmd. true: Pres cmd, temp read.
    void CalculateFilteredAltVs(float dt);
    float CalculateAlpha(float f, float dt);
    float altf = 0;      // Filtered altitude [m]
    float vs = 0;        // Vertical speed [m/s]
    float altfp = 0;     // Previous filtered altitude
    float fCutAlt = 0.1; // [Hz]
public:
    Baro() = default;
    virtual ~Baro() = default;
    bool Init();
    void Update(float dt);
    float GetAlt() {return altf; };
    float GetVario() {return vs; };
};

#endif /* BARO_HPP */