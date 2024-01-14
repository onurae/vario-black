/*******************************************************************************************
 *                                                                                         *
 *    Utility for Vario-Black                                                              *
 *                                                                                         *
 *    Copyright (c) 2023 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#include "util.hpp"

void Delay(unsigned long interval)
{
    unsigned long previous = millis();
    unsigned long current = previous;
    while (current - previous < interval)
    {
        current = millis();
    }
}

bool IsButtonPressed(int8_t button)
{
    return (digitalRead(button) == LOW) ? true : false;
}

void LoopForever()
{
    while (true)
    {
        Delay(1000);
    }
}