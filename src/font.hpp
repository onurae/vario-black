/*******************************************************************************************
 *                                                                                         *
 *    Fonts for Vario-Black                                                                *
 *                                                                                         *
 *    Copyright (c) 2024 Onur AKIN <https://github.com/onurae>                             *
 *    Licensed under the MIT License.                                                      *
 *                                                                                         *
 ******************************************************************************************/

#ifndef FONT_HPP
#define FONT_HPP

const uint8_t Icons21x21[] PROGMEM = {
    21, 21, 32, 35,
    0x15, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x80, 0x07, 0x00, 0xC0, 0x07, 0x00, 0xE0, 0x07, 0x00, 0xF0, 0x07, 0x00, 0xE0, 0x07, 0x00, 0xC0, 0x07, 0x00, 0x90, 0x07, 0x00, 0x38, 0x07, 0x00, 0x1C, 0x06, 0x00, 0x0E, 0x06, 0x00, 0x0F, 0x06, 0x00, 0x0E, 0x06, 0x20, 0x1C, 0x06, 0x30, 0x38, 0x06, 0xF8, 0x73, 0x06, 0xFC, 0xE3, 0x06, 0xF8, 0xC3, 0x07, 0x30, 0x80, 0x07, 0x20, 0x00, 0x07,
    0x15, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x0E, 0x00, 0x10, 0x1C, 0x00, 0x18, 0x38, 0x00, 0xFC, 0x71, 0x00, 0xFE, 0x71, 0x00, 0xFC, 0x71, 0x00, 0x18, 0x38, 0x00, 0x10, 0x1C, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x07, 0x02, 0x80, 0x03, 0x06, 0xC0, 0xE1, 0x0F, 0xC0, 0xE1, 0x1F, 0xC0, 0xE1, 0x0F, 0x80, 0x03, 0x06, 0x00, 0x07, 0x02, 0x00, 0x0E, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x18, 0x00,
    0x09, 0x1C, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x63, 0x00, 0x00, 0x41, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x7F, 0x00, 0x00, 0x41, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x41, 0x00, 0x00, 0x41, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Arial16x21, Regular-22. Adjusted one pixel @5. One column added to the left. "." and "1" shifted 2 pixels left.
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

const uint8_t c64[] PROGMEM =
    {
        7, 8, 32, '~' + 7,
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
        0x02, 0x5F, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, // !
        0x06, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07, 0x00, // "
        0x07, 0x14, 0x7F, 0x7F, 0x14, 0x7F, 0x7F, 0x14, // #
        0x06, 0x24, 0x2E, 0x6B, 0x6B, 0x3A, 0x12, 0x00, // $
        0x06, 0x63, 0x73, 0x18, 0x0C, 0x67, 0x63, 0x00, // %
        0x07, 0x32, 0x7F, 0x4D, 0x4D, 0x77, 0x72, 0x50, // &
        0x04, 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, // '
        0x04, 0x1C, 0x3E, 0x63, 0x41, 0x00, 0x00, 0x00, // (
        0x04, 0x41, 0x63, 0x3E, 0x1C, 0x00, 0x00, 0x00, // )
        0x07, 0x08, 0x2A, 0x3E, 0x1C, 0x3E, 0x2A, 0x08, // *
        0x06, 0x08, 0x08, 0x3E, 0x3E, 0x08, 0x08, 0x00, // +
        0x03, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00, // ,
        0x06, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, // -
        0x02, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, // .
        0x07, 0x40, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, // /
        0x06, 0x3E, 0x7F, 0x49, 0x45, 0x7F, 0x3E, 0x00, // 0
        0x06, 0x40, 0x44, 0x7F, 0x7F, 0x40, 0x40, 0x00, // 1
        0x06, 0x62, 0x73, 0x59, 0x49, 0x4F, 0x46, 0x00, // 2
        0x06, 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00, // 3
        0x07, 0x18, 0x1C, 0x16, 0x13, 0x7F, 0x7F, 0x10, // 4
        0x06, 0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00, // 5
        0x06, 0x3E, 0x7F, 0x49, 0x49, 0x7B, 0x32, 0x00, // 6
        0x06, 0x01, 0x01, 0x79, 0x7D, 0x07, 0x03, 0x00, // 7
        0x06, 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, // 8
        0x06, 0x26, 0x6F, 0x49, 0x49, 0x7F, 0x3E, 0x00, // 9
        0x02, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, // :
        0x03, 0x80, 0xC4, 0x44, 0x00, 0x00, 0x00, 0x00, // ;
        0x06, 0x08, 0x1C, 0x36, 0x63, 0x41, 0x41, 0x00, // <
        0x06, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, // =
        0x06, 0x41, 0x41, 0x63, 0x36, 0x1C, 0x08, 0x00, // >
        0x06, 0x02, 0x03, 0x51, 0x59, 0x0F, 0x06, 0x00, // ?
        0x06, 0x3E, 0x7F, 0x41, 0x4D, 0x6F, 0x2E, 0x00, // @
        0x06, 0x7C, 0x7E, 0x13, 0x13, 0x7E, 0x7C, 0x00, // A
        0x06, 0x7F, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, // B
        0x06, 0x3E, 0x7F, 0x41, 0x41, 0x63, 0x22, 0x00, // C
        0x06, 0x7F, 0x7F, 0x41, 0x41, 0x7F, 0x3E, 0x00, // D
        0x06, 0x7F, 0x7F, 0x49, 0x49, 0x41, 0x41, 0x00, // E
        0x06, 0x7F, 0x7F, 0x09, 0x09, 0x01, 0x01, 0x00, // F
        0x06, 0x3E, 0x7F, 0x41, 0x49, 0x7B, 0x3A, 0x00, // G
        0x06, 0x7F, 0x7F, 0x08, 0x08, 0x7F, 0x7F, 0x00, // H
        0x04, 0x41, 0x7F, 0x7F, 0x41, 0x00, 0x00, 0x00, // I
        0x06, 0x20, 0x60, 0x41, 0x7F, 0x3F, 0x01, 0x00, // J
        0x06, 0x7F, 0x7F, 0x1C, 0x36, 0x63, 0x41, 0x00, // K
        0x06, 0x7F, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, // L
        0x07, 0x7F, 0x7F, 0x06, 0x0C, 0x06, 0x7F, 0x7F, // M
        0x06, 0x7F, 0x7F, 0x0C, 0x18, 0x7F, 0x7F, 0x00, // N
        0x06, 0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E, 0x00, // O
        0x06, 0x7F, 0x7F, 0x09, 0x09, 0x0F, 0x06, 0x00, // P
        0x06, 0x1E, 0x3F, 0x21, 0x61, 0x7F, 0x5E, 0x00, // Q
        0x06, 0x7F, 0x7F, 0x19, 0x39, 0x6F, 0x46, 0x00, // R
        0x06, 0x26, 0x6F, 0x49, 0x49, 0x7B, 0x32, 0x00, // S
        0x06, 0x01, 0x01, 0x7F, 0x7F, 0x01, 0x01, 0x00, // T
        0x06, 0x3F, 0x7F, 0x40, 0x40, 0x7F, 0x3F, 0x00, // U
        0x06, 0x1F, 0x3F, 0x60, 0x60, 0x3F, 0x1F, 0x00, // V
        0x07, 0x7F, 0x7F, 0x30, 0x18, 0x30, 0x7F, 0x7F, // W
        0x06, 0x41, 0x63, 0x3E, 0x3E, 0x63, 0x41, 0x00, // X
        0x06, 0x07, 0x0F, 0x78, 0x78, 0x0F, 0x07, 0x00, // Y
        0x06, 0x61, 0x71, 0x59, 0x4D, 0x47, 0x43, 0x00, // Z
        0x04, 0x7F, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00, // [
        0x07, 0x02, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, // BackSlash
        0x04, 0x41, 0x41, 0x7F, 0x7F, 0x00, 0x00, 0x00, // ]
        0x06, 0x08, 0x0C, 0xFE, 0xFE, 0x0C, 0x08, 0x00, // ^
        0x07, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // _
        0x07, 0x1C, 0x3E, 0x63, 0x41, 0x63, 0x14, 0x14, // `
        0x06, 0x20, 0x74, 0x54, 0x54, 0x7C, 0x78, 0x00, // a
        0x06, 0x7F, 0x7F, 0x44, 0x44, 0x7C, 0x38, 0x00, // b
        0x05, 0x38, 0x7C, 0x44, 0x44, 0x44, 0x00, 0x00, // c
        0x06, 0x38, 0x7C, 0x44, 0x44, 0x7F, 0x7F, 0x00, // d
        0x06, 0x38, 0x7C, 0x54, 0x54, 0x5C, 0x18, 0x00, // e
        0x05, 0x08, 0x7E, 0x7F, 0x09, 0x09, 0x00, 0x00, // f
        0x06, 0x98, 0xBC, 0xA4, 0xA4, 0xFC, 0x7C, 0x00, // g
        0x06, 0x7F, 0x7F, 0x04, 0x04, 0x7C, 0x78, 0x00, // h
        0x04, 0x44, 0x7D, 0x7D, 0x40, 0x00, 0x00, 0x00, // i
        0x05, 0x80, 0x80, 0x80, 0xFD, 0x7D, 0x00, 0x00, // j
        0x06, 0x7F, 0x7F, 0x10, 0x38, 0x6C, 0x44, 0x00, // k
        0x04, 0x41, 0x7F, 0x7F, 0x40, 0x00, 0x00, 0x00, // l
        0x07, 0x78, 0x7C, 0x0C, 0x38, 0x0C, 0x7C, 0x78, // m
        0x06, 0x7C, 0x7C, 0x04, 0x04, 0x7C, 0x78, 0x00, // n
        0x06, 0x38, 0x7C, 0x44, 0x44, 0x7C, 0x38, 0x00, // o
        0x06, 0xFC, 0xFC, 0x24, 0x24, 0x3C, 0x18, 0x00, // p
        0x06, 0x18, 0x3C, 0x24, 0x24, 0xFC, 0xFC, 0x00, // q
        0x06, 0x7C, 0x7C, 0x04, 0x04, 0x0C, 0x08, 0x00, // r
        0x06, 0x48, 0x5C, 0x54, 0x54, 0x74, 0x24, 0x00, // s
        0x05, 0x04, 0x3F, 0x7F, 0x44, 0x44, 0x00, 0x00, // t
        0x06, 0x3C, 0x7C, 0x40, 0x40, 0x7C, 0x7C, 0x00, // u
        0x06, 0x1C, 0x3C, 0x60, 0x60, 0x3C, 0x1C, 0x00, // v
        0x07, 0x1C, 0x7C, 0x60, 0x38, 0x60, 0x7C, 0x1C, // w
        0x06, 0x44, 0x6C, 0x38, 0x38, 0x6C, 0x44, 0x00, // x
        0x06, 0x9C, 0xBC, 0xA0, 0xE0, 0x7C, 0x3C, 0x00, // y
        0x06, 0x44, 0x64, 0x74, 0x5C, 0x4C, 0x44, 0x00, // z
        0x05, 0x08, 0x3E, 0x7F, 0x41, 0x41, 0x00, 0x00, // {
        0x02, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, // |
        0x05, 0x41, 0x41, 0x7F, 0x3E, 0x08, 0x00, 0x00, // }
        0x05, 0x10, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, // ~
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // DEL
        0x06, 0x08, 0x0C, 0x7E, 0x7E, 0x0C, 0x08, 0x00, // up, 128
        0x06, 0x10, 0x30, 0x7E, 0x7E, 0x30, 0x10, 0x00, // down, 129
        0x07, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, // back, 130
        0x07, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x1F, 0x1F, // enter, 131
        0x05, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00, // dot, 132
        0x07, 0x30, 0x60, 0xE0, 0x70, 0x38, 0x1C, 0x0E  // tick, 133
};

#endif /* FONT_HPP */