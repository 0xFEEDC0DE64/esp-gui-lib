#include "reverseprogressbar.h"

// 3rdparty lib includes
#include <cpputils.h>

// local includes
#include "tftinstance.h"

namespace espgui {
ReverseProgressBar::ReverseProgressBar(int x, int y, int width, int height, int min, int max, uint32_t color) :
    m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_min{min}, m_max{max}, m_color{color}
{
}

void ReverseProgressBar::start()
{
    m_lastValue = m_x+m_width-1;
    tft.drawRect(m_x, m_y, m_width, m_height, TFT_WHITE);
}

void ReverseProgressBar::redraw(int value)
{
    value = cpputils::mapValueClamped(value, m_min, m_max, m_x+m_width-1, m_x+1);

    if (value < m_lastValue)
        tft.fillRect(value, m_y+1, m_lastValue-value, m_height-2, m_color);
    else if (value > m_lastValue)
        tft.fillRect(m_lastValue, m_y+1, value-m_lastValue, m_height-2, TFT_BLACK);

    m_lastValue = value;
}
} // namespace espgui
