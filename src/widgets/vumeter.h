#pragma once

// system includes
#include <cstdint>

// forward declares
namespace espgui { class TftInterface; }

namespace espgui {
class VuMeter
{
public:
    void start(TftInterface &tft);
    void redraw(TftInterface &tft, float value);

private:
    float ltx;         // Saved x coord of bottom of needle
    uint16_t osx, osy; // Saved x & y coords
};
} // namespace espgui
