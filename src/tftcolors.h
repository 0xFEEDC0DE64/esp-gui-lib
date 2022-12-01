#pragma once

// system includes
#include <cstdint>

namespace espgui {

// Colour conversion
// Convert 8 bit red, green and blue to 16 bits
constexpr uint16_t color565(uint8_t red, uint8_t green, uint8_t blue) noexcept
{
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}

/***************************************************************************************
**                         Section 6: Colour enumeration
***************************************************************************************/
// Default color definitions
constexpr uint16_t TFT_BLACK       = color565(  0,   0,   0);
constexpr uint16_t TFT_NAVY        = color565(  0,   0, 128);
constexpr uint16_t TFT_DARKGREEN   = color565(  0, 128,   0);
constexpr uint16_t TFT_DARKCYAN    = color565(  0, 128, 128);
constexpr uint16_t TFT_MAROON      = color565(128,   0,   0);
constexpr uint16_t TFT_PURPLE      = color565(128,   0, 128);
constexpr uint16_t TFT_OLIVE       = color565(128, 128,   0);
constexpr uint16_t TFT_LIGHTGREY   = color565(211, 211, 211);
constexpr uint16_t TFT_DARKGREY    = color565(128, 128, 128);
constexpr uint16_t TFT_BLUE        = color565(  0,   0, 255);
constexpr uint16_t TFT_GREEN       = color565(  0, 255,   0);
constexpr uint16_t TFT_CYAN        = color565(  0, 255, 255);
constexpr uint16_t TFT_RED         = color565(255,   0,   0);
constexpr uint16_t TFT_MAGENTA     = color565(255,   0, 255);
constexpr uint16_t TFT_YELLOW      = color565(255, 255,   0);
constexpr uint16_t TFT_WHITE       = color565(255, 255, 255);
constexpr uint16_t TFT_GREY        = 0x5AEB;
constexpr uint16_t TFT_ORANGE      = color565(255, 180,   0);
constexpr uint16_t TFT_GREENYELLOW = color565(180, 255,   0);
constexpr uint16_t TFT_PINK        = color565(255, 192, 203); //Lighter pink, was 0xFC9F
constexpr uint16_t TFT_BROWN       = color565(150,  75,   0);
constexpr uint16_t TFT_GOLD        = color565(255, 215,   0);
constexpr uint16_t TFT_SILVER      = color565(192, 192, 192);
constexpr uint16_t TFT_SKYBLUE     = color565(135, 206, 235);
constexpr uint16_t TFT_VIOLET      = color565(180,  46, 226);
constexpr uint16_t TFT_NICEBLUE    = color565(59, 163, 255);

} // namespace espgui
