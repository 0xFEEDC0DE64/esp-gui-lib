#pragma once

// system includes
#include <string>

namespace espgui {
class Label
{
public:
    Label(int x, int y);

    int x() const { return m_x; };
    int y() const { return m_y; };

    void start();
    void redraw(std::string_view str, bool forceRedraw = false);
    void clear();

private:
    const int m_x;
    const int m_y;

    std::string m_lastStr;
    int m_lastFont;
    int m_lastColor;

    int m_lastWidth;
    int m_lastHeight;
};
} // namespace espgui
