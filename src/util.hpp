/*******************************************************************************************
 *                                                                                         *
 *    Utility for Vario-Black                                                              *
 *                                                                                         *
 *    Copyright (c) 2023 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <Arduino.h>
#include <SPI.h>

#define POT_ADDRESS 0x11
#define POT_CS 7
int DigitalPotWrite(int value);

void Delay(unsigned long interval);
bool IsButtonPressed(int8_t button);
void LoopForever();

#endif /* UTIL_HPP */