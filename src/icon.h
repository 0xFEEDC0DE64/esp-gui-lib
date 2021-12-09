#pragma once

// system includes
#include <cstdint>

namespace espgui {
template<uint16_t width, uint16_t height>
struct Icon
{
    static constexpr auto WIDTH=width;
    static constexpr auto HEIGHT=height;

    const unsigned short buffer[width*height];
    const char * const name{};
    
};
} // namespace espgui
