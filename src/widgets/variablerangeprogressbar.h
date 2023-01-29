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
class VariableRangeProgressBar
{
public:
    VariableRangeProgressBar(int x, int y, int width, int height, int min, int max, uint32_t color = TFT_YELLOW);

    void start(TftInterface &tft);
    void redraw(TftInterface &tft, int value);

    void setMin(int min) { m_min = min; }
    void setMax(int max) { m_max = max; }
    void setMinMax(int min, int max) { m_min = min; m_max = max; }

    int getMin() const { return m_min; }
    int getMax() const { return m_max; }

private:
    const int m_x;
    const int m_y;
    const int m_width;
    const int m_height;
    int m_min;
    int m_max;
    const uint32_t m_color;

    int m_lastValue{};
};
} // namespace espgui
