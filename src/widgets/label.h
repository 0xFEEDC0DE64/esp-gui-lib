#pragma once

// system includes
#include <string>

// forward declares
namespace espgui {
class TftInterface;
} // namespace espgui

namespace espgui {
class Label
{
public:
    Label(int x, int y);

    int x() const { return m_x; }
    int y() const { return m_y; }

    void start(TftInterface &tft);
    void redraw(TftInterface &tft, std::string_view str, uint16_t color, uint16_t bgcolor, uint8_t font, bool forceRedraw = false);
    void clear(TftInterface &tft, uint16_t bgcolor);

private:
    const int m_x;
    const int m_y;

    std::string m_lastStr;
    uint16_t m_lastColor;
    uint8_t m_lastFont;

    int m_lastWidth;
    int m_lastHeight;
};
} // namespace espgui
