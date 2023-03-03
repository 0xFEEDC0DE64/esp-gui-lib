#pragma once

// system includes
#include <string>
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

// forward declares
namespace espgui {
class TftInterface;
class FontRenderer;
} // namespace espgui

namespace espgui {
class ScrollLabel
{
public:
    ScrollLabel(int x, int y, int width, int scrollSpeed);
    ScrollLabel(int x, int y);

    int x() const { return m_x; }
    int y() const { return m_y; }
    const std::optional<int>& width() { return m_width; }
    int scrollSpeed() const { return m_scrollSpeed; }

    void start(TftInterface &tft);
    void start(TftInterface &tft, int width);
    void redraw(TftInterface &tft, std::string_view str, uint16_t color, uint16_t bgcolor, uint8_t font, bool forceRedraw = false);
    void redraw(TftInterface &tft, FontRenderer &fontRenderer, std::string_view str, uint16_t color, uint16_t bgcolor, uint8_t font, bool forceRedraw = false);
    void clear(TftInterface &tft, uint16_t bgcolor);

private:
    const int m_x;
    const int m_y;
    std::optional<int> m_width;
    const int m_scrollSpeed;

    std::string m_lastStr;
    std::string m_lastStrScroll;
    uint16_t m_lastColor;
    uint8_t m_lastFont;

    int m_lastWidth;
    int m_lastHeight;

    espchrono::millis_clock::time_point m_lastScrollTime;
    int m_scrollOffset;
};
} // namespace espgui
