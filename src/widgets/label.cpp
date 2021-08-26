#include "label.h"

// local includes
#include "tftinstance.h"

namespace espgui {
Label::Label(int x, int y) :
    m_x{x},
    m_y{y}
{
}

void Label::start()
{
    m_lastStr.clear();
    m_lastFont = -1;
    m_lastColor = -1;

    m_lastWidth = 0;
    m_lastHeight = 0;
}

void Label::redraw(std::string_view str, bool forceRedraw)
{
    if (m_lastStr == str &&
        m_lastFont == tft.textfont &&
        m_lastColor == tft.textcolor &&
        !forceRedraw)
        return;

    const auto renderedWidth = str.empty() ? 0 : tft.drawString(str.data(), m_x, m_y);
    const auto renderedHeight = tft.fontHeight();

    if (renderedWidth < m_lastWidth)
        tft.fillRect(m_x + renderedWidth, m_y,
                     m_lastWidth - renderedWidth, m_lastHeight,
                     tft.textbgcolor);

    if (renderedHeight < m_lastHeight)
        tft.fillRect(m_x, m_y + renderedHeight,
                     renderedWidth, m_lastHeight - renderedHeight,
                     tft.textbgcolor);

    m_lastStr = str;
    m_lastFont = tft.textfont;
    m_lastColor = tft.textcolor;

    m_lastWidth = renderedWidth;
    m_lastHeight = renderedHeight;
}

void Label::clear()
{
    if (m_lastWidth || m_lastHeight)
        tft.fillRect(m_x, m_y, m_lastWidth, m_lastHeight, tft.textbgcolor);

    start();
}
}
