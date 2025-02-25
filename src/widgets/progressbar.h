#pragma once

// system includes
#include <cstdint>

// 3rdparty lib includes
#include <TFT_eSPI.h>

// local includes
#include "tftcolors.h"

// forward declares
namespace espgui { class TftInterface; }

namespace espgui {
class ProgressBar
{
public:
    ProgressBar(int x, int y, int width, int height, int min, int max, uint32_t color = TFT_YELLOW, uint32_t backgroundColor = TFT_BLACK);

    void start(TftInterface &tft);
    void redraw(TftInterface &tft, int value);

    void changeColor(TftInterface &tft, const uint32_t color = TFT_YELLOW, const uint32_t backgroundColor = TFT_BLACK);

private:
    const int m_x;
    const int m_y;
    const int m_width;
    const int m_height;
    const int m_min;
    const int m_max;
    uint32_t m_color;
    uint32_t m_backgroundColor;

    int m_lastValue{};
};
} // namespace espgui
