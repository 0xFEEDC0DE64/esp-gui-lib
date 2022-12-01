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
class ReverseProgressBar
{
public:
    ReverseProgressBar(int x, int y, int width, int height, int min, int max, uint32_t color=TFT_YELLOW);

    void start(TftInterface &tft);
    void redraw(TftInterface &tft, int value);

private:
    const int m_x;
    const int m_y;
    const int m_width;
    const int m_height;
    const int m_min;
    const int m_max;
    const uint32_t m_color;

    int m_lastValue{};
};
} // namespace espgui
