#include "scrolllabel.h"

// system includes
#include <string_view>

// 3rdparty lib includes
#include <fontrenderer.h>
#include <tftcolors.h>

// local includes
#include "tftinterface.h"
#include "richtextrenderer.h"

using namespace std::chrono_literals;

namespace espgui {
ScrollLabel::ScrollLabel(int x, int y, int width, int scrollSpeed) :
        m_x{x},
        m_y{y},
        m_width{width},
        m_scrollSpeed{scrollSpeed},
        m_lastScrollTime{espchrono::millis_clock::now()},
        m_scrollOffset{0}
{}

ScrollLabel::ScrollLabel(int x, int y) :
        m_x{x},
        m_y{y},
        m_width{std::nullopt},
        m_scrollSpeed{500},
        m_lastScrollTime{espchrono::millis_clock::now()},
        m_scrollOffset{0}
{}

void ScrollLabel::start(TftInterface &tft)
{
    m_lastStr.clear();
    m_lastFont = -1;
    m_lastColor = -1;

    m_lastWidth = 0;
    m_lastHeight = 0;

    //m_lastScrollTime = espchrono::millis_clock::now();
    //m_scrollOffset = 0;
}

void ScrollLabel::start(TftInterface &tft, int width)
{
    m_width = width;
    start(tft);
}

void ScrollLabel::redraw(TftInterface &tft, std::string_view str, uint16_t color, uint16_t bgcolor, uint8_t font, bool forceRedraw)
{
    espgui::FontRenderer fontRenderer{tft};
    redraw(tft, fontRenderer, str, color, bgcolor, font, forceRedraw);
}

void ScrollLabel::redraw(TftInterface &tft, FontRenderer &fontRenderer, std::string_view str, uint16_t color, uint16_t bgcolor, uint8_t font, bool forceRedraw)
{
    const auto char_width = fontRenderer.textWidth(str, font) / std::max(1U, str.length());
    const auto max_chars = m_width ? (*m_width / std::max(1U, char_width)) : 0;
    bool scroll = (str.length() > max_chars && m_width);

    // ESP_LOGI("ScrollLabel", "str: %s, scrolling: %s, strlen: %d, maxchars: %d", str.data(), str.length() > max_chars ? "true" : "false", str.length(), max_chars);

    if (m_lastStr == str &&
        m_lastColor == color &&
        m_lastFont == font &&
        !forceRedraw &&
        (str.length() <= max_chars || !m_width))
        return;

    if (str.contains("&"))
        scroll = false;

    if (scroll)
    {
        const auto now = espchrono::millis_clock::now();
        const auto elapsed = espchrono::ago(m_lastScrollTime);
        if (elapsed > (m_scrollSpeed * (m_scrollOffset == 0 ? 3ms : 1ms)))
        {
            m_lastScrollTime = now;
            m_scrollOffset++;
            if (m_scrollOffset > str.length() - max_chars)
                m_scrollOffset = 0;
        }
        str = str.substr(m_scrollOffset, max_chars);
    }
    else
        m_scrollOffset = 0;

    if (m_lastColor == color &&
        m_lastFont == font &&
        m_lastStrScroll == str)
        return;

    const auto renderedWidth = renderRichText(tft, fontRenderer, str, m_x, m_y, color, bgcolor, font);
    const auto renderedHeight = fontRenderer.fontHeight(font);

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

    m_lastStrScroll = str;
}

void ScrollLabel::clear(TftInterface &tft, uint16_t bgcolor)
{
    if (m_lastWidth || m_lastHeight)
        tft.fillRect(m_x, m_y, m_lastWidth, m_lastHeight, bgcolor);

    start(tft);
}
} // namespace espgui
