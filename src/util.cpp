/*******************************************************************************************
 *                                                                                         *
 *    Utility for Vario-Black                                                              *
 *                                                                                         *
 *    Copyright (c) 2022 Onur AKIN <https://github.com/onurae>                             *
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