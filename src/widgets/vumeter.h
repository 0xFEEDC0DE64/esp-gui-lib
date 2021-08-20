#pragma once

// system includes
#include <cstdint>

namespace espgui {
class VuMeter
{
public:
    void start();
    void redraw(float value);

private:
    float ltx;         // Saved x coord of bottom of needle
    uint16_t osx, osy; // Saved x & y coords
};
} // namespace espgui
