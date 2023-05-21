/*******************************************************************************************
 *                                                                                         *
 *    Fonts for Vario-Black                                                                *
 *                                                                                         *
 *    Copyright (c) 2023 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#ifndef FONT_HPP
#define FONT_HPP

// Arial16x21, Regular-22. Adjusted one pixel @5. One column added to the left. Dot shifted 2 pixels left.
const uint8_t Arial16x21[] PROGMEM = {
    16, 21, '-', '9',
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // -
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x1F, 0x00, 0xF0, 0x07, 0x00, 0xFE, 0x00, 0xE0, 0x0F, 0x00, 0xFC, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // /
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x00, 0xF8, 0xFF, 0x03, 0xFE, 0xFF, 0x0F, 0x3E, 0x80, 0x0F, 0x0F, 0x00, 0x1E, 0x07, 0x00, 0x1C, 0x07, 0x00, 0x1C, 0x07, 0x00, 0x1C, 0x07, 0x00, 0x1C, 0x0F, 0x00, 0x1E, 0x3E, 0x80, 0x0F, 0xFE, 0xFF, 0x0F, 0xF8, 0xFF, 0x03, 0xC0, 0xFF, 0x00, // 0
    0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x70, 0x00, 0x00, 0x30, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x00, 0xFE, 0xFF, 0x1F, 0xFF, 0xFF, 0x1F, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 1
    0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18, 0x3C, 0x00, 0x1E, 0x3E, 0x00, 0x1F, 0x0E, 0x80, 0x1F, 0x07, 0xC0, 0x1D, 0x07, 0xE0, 0x1C, 0x07, 0x70, 0x1C, 0x07, 0x38, 0x1C, 0x0F, 0x1C, 0x1C, 0x0E, 0x0E, 0x1C, 0xFE, 0x07, 0x1C, 0xFC, 0x03, 0x1C, 0xF8, 0x00, 0x1C, 0x00, 0x00, 0x00, // 2
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x80, 0x01, 0x1C, 0x80, 0x07, 0x1E, 0x80, 0x0F, 0x0E, 0x00, 0x0F, 0x07, 0x00, 0x1C, 0x07, 0x06, 0x1C, 0x07, 0x06, 0x1C, 0x07, 0x06, 0x1C, 0x07, 0x07, 0x1C, 0x0E, 0x07, 0x1E, 0xFE, 0x0F, 0x0F, 0xFC, 0xFD, 0x0F, 0xF8, 0xF8, 0x07, 0x00, 0xF0, 0x01, // 3
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xEF, 0x00, 0x80, 0xE7, 0x00, 0xC0, 0xE3, 0x00, 0xE0, 0xE0, 0x00, 0x78, 0xE0, 0x00, 0x3C, 0xE0, 0x00, 0xFE, 0xFF, 0x1F, 0xFF, 0xFF, 0x1F, 0xFF, 0xFF, 0x1F, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, // 4
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x01, 0xF8, 0x87, 0x07, 0xFF, 0x87, 0x0F, 0xFF, 0x07, 0x0F, 0x07, 0x03, 0x1C, 0x87, 0x03, 0x1C, 0x87, 0x03, 0x1C, 0x87, 0x03, 0x1C, 0x87, 0x03, 0x1C, 0x87, 0x03, 0x1E, 0x07, 0x0F, 0x0F, 0x07, 0xFF, 0x07, 0x07, 0xFE, 0x03, 0x00, 0xF8, 0x01, // 5
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0xF0, 0xFF, 0x03, 0xFC, 0xFF, 0x07, 0x3E, 0x0E, 0x0F, 0x0E, 0x07, 0x0E, 0x07, 0x03, 0x1C, 0x87, 0x03, 0x1C, 0x87, 0x03, 0x1C, 0x87, 0x03, 0x1C, 0x87, 0x07, 0x1E, 0x0F, 0x0F, 0x0F, 0x1E, 0xFF, 0x0F, 0x1C, 0xFE, 0x07, 0x18, 0xF8, 0x01, // 6
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x1E, 0x07, 0xE0, 0x1F, 0x07, 0xFC, 0x1F, 0x07, 0xFF, 0x01, 0x87, 0x1F, 0x00, 0xE7, 0x03, 0x00, 0xF7, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x07, 0x00, 0x00, // 7
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x78, 0xF8, 0x07, 0xFC, 0xFC, 0x0F, 0xFE, 0x1D, 0x0F, 0x8F, 0x07, 0x1E, 0x07, 0x07, 0x1C, 0x07, 0x07, 0x1C, 0x07, 0x07, 0x1C, 0x07, 0x07, 0x1C, 0x8F, 0x0F, 0x1C, 0xFE, 0x1D, 0x0E, 0xFC, 0xFC, 0x0F, 0x78, 0xF8, 0x07, 0x00, 0xF0, 0x01, // 8
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x03, 0xFC, 0x0F, 0x07, 0xFE, 0x1F, 0x0F, 0x1E, 0x1E, 0x1E, 0x0F, 0x3C, 0x1C, 0x07, 0x38, 0x1C, 0x07, 0x38, 0x1C, 0x07, 0x38, 0x1C, 0x07, 0x18, 0x1C, 0x0E, 0x1C, 0x0E, 0x1E, 0x8E, 0x0F, 0xFC, 0xFF, 0x07, 0xF8, 0xFF, 0x01, 0xE0, 0x7F, 0x00  // 9
};

#endif /* FONT_HPP */