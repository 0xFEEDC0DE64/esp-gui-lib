#pragma once

// 3rdparty lib includes
#include <TFT_eSPI.h>

namespace espgui {
extern TFT_eSPI tft;
inline bool isLandscape()
{
    return (tft.getRotation() == 1 || tft.getRotation() == 3);
}
}
