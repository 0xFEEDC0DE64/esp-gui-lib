#pragma once

// system includes
#include <cstdint>

// forward declares
namespace espgui { class TftInterface; }

namespace espgui {
class VerticalMeter
{
public:
    VerticalMeter(const char *text, const char *format, int x, int y);

    void start(TftInterface &tft);
    void redraw(TftInterface &tft, float value, float min, float max);

private:
    const char * const m_text;
    const char * const m_format;
    const int m_x;
    const int m_y;

    float m_oldValue{};
};
} // namespace espgui
