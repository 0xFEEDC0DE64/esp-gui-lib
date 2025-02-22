#pragma once

// system includes
#include <string>

namespace espgui {
class ScrollingLabel
{
public:
    ScrollingLabel(int x, int y);

    int x() const { return m_x; };
    int y() const { return m_y; };

    void start();
    void redraw(const std::string& str, bool forceRedraw = false);
    void clear();

private:
    const int m_x;
    const int m_y;

    std::string m_lastStr;
    std::string m_str;
    std::string_view visibleStr;
    int m_lastFont;
    int m_lastColor;

    int m_lastWidth;
    int m_lastHeight;
};

class AutoScrollingLabel : public ScrollingLabel // needs void update()
{
};
} // namespace espgui
