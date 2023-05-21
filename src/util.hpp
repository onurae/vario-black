/*******************************************************************************************
 *                                                                                         *
 *    Utility for Vario-Black                                                              *
 *                                                                                         *
 *    Copyright (c) 2022 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <Arduino.h>

void Delay(unsigned long interval);
bool IsButtonPressed(int8_t button);
void LoopForever();

#endif /* UTIL_HPP */