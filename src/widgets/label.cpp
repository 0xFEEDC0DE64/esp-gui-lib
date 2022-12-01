#include "label.h"

// local includes
#include "tftinterface.h"
#include "richtextrenderer.h"

namespace espgui {
Label::Label(int x, int y) :
    m_x{x},
    m_y{y}
{
}

void Label::start(TftInterface &tft)
{
    m_lastStr.clear();
    m_lastFont = -1;
    m_lastColor = -1;

    m_lastWidth = 0;
    m_lastHeight = 0;
}

void Label::redraw(TftInterface &tft, std::string_view str, uint16_t color, uint16_t bgcolor, uint8_t font, bool forceRedraw)
{
    if (m_lastStr == str &&
        m_lastColor == color &&
        m_lastFont == font &&
        !forceRedraw)
        return;

    const auto renderedWidth = renderRichText(tft, str, m_x, m_y, color, bgcolor, font);
    const auto renderedHeight = tft.fontHeight(font);

    if (renderedWidth < m_lastWidth)
        tft.fillRect(m_x + renderedWidth, m_y,
                     m_lastWidth - renderedWidth, m_lastHeight,
                     bgcolor);

    if (renderedHeight < m_lastHeight)
        tft.fillRect(m_x, m_y + renderedHeight,
                     renderedWidth, m_lastHeight - renderedHeight,
                     bgcolor);

    m_lastStr = str;
    m_lastColor = color;
    m_lastFont = font;

    m_lastWidth = renderedWidth;
    m_lastHeight = renderedHeight;
}

void Label::clear(TftInterface &tft, uint16_t bgcolor)
{
    if (m_lastWidth || m_lastHeight)
        tft.fillRect(m_x, m_y, m_lastWidth, m_lastHeight, bgcolor);

    start(tft);
}
}
