#include "slider.h"

// 3rdparty lib includes
#include <cpputils.h>

// local includes
#include "tftinstance.h"

namespace espgui {
Slider::Slider(int x, int y, int width, int height, int min, int max, uint32_t leftColor, uint32_t rightColor, uint32_t lineColor) :
    m_x{x},
    m_y{y},
    m_width{width},
    m_height{height},
    m_min{min},
    m_max{max},
    m_leftColor{leftColor},
    m_rightColor{rightColor},
    m_lineColor{lineColor}
{}

void Slider::start()
{
    m_lastValue = m_x+1;
    tft.drawRect(m_x, m_y, m_width, m_height, TFT_WHITE);
    tft.fillRect(m_x+1, m_y+1, m_width-2, m_height-2, m_rightColor);
}

void Slider::redraw(int value)
{
    // slider with 1 pixel white line at position of value (mapped). Left side of line is leftColor, right side is rightColor
    value = cpputils::mapValueClamped(value, m_min, m_max, m_x+1, m_x+m_width-1);

    if (value < m_lastValue)
        tft.fillRect(value, m_y+1, m_lastValue-value+1, m_height-2, m_rightColor);
    else if (value > m_lastValue)
        tft.fillRect(m_lastValue, m_y+1, value-m_lastValue, m_height-2, m_leftColor);

    m_lastValue = value;

    // draw slider line
    tft.drawFastVLine(std::min(value, m_x+m_width-2), m_y+1, m_height-2, m_lineColor);
}
} // namespace espgui
