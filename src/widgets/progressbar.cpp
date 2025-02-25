#include "progressbar.h"

// 3rdparty lib includes
#include <cpputils.h>

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {
ProgressBar::ProgressBar(int x, int y, int width, int height, int min, int max, uint32_t color, uint32_t backgroundColor) :
    m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_min{min}, m_max{max}, m_color{color}, m_backgroundColor{backgroundColor}
{
}

void ProgressBar::start(TftInterface &tft)
{
    m_lastValue = m_x+1;
    tft.drawRect(m_x, m_y, m_width, m_height, TFT_WHITE);
    tft.fillRect(m_x+1, m_y+1, m_width-2, m_height-2, m_backgroundColor);
}

void ProgressBar::redraw(TftInterface &tft, int value)
{
    value = cpputils::mapValueClamped(value, m_min, m_max, m_x+1, m_x+m_width-1);

    if (value < m_lastValue)
        tft.fillRect(value, m_y+1, m_lastValue-value, m_height-2, m_backgroundColor);
    else if (value > m_lastValue)
        tft.fillRect(m_lastValue, m_y+1, value-m_lastValue, m_height-2, m_color);

    m_lastValue = value;
}

void ProgressBar::changeColor(TftInterface &tft, const uint32_t color, const uint32_t backgroundColor)
{
    if (color != m_color)
    {
        // redraw already drawn area in new color
        tft.fillRect(m_x+1, m_y+1, m_lastValue-m_x-1, m_height-2, color);
        m_color = color;
    }

    if (backgroundColor != m_backgroundColor)
    {
        // redraw background in new color
        tft.fillRect(m_x+1, m_y+1, m_width-2, m_height-2, backgroundColor);
        m_backgroundColor = backgroundColor;
    }
}

} // namespace espgui
