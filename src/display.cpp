#include "display.h"

// 3rdparty lib includes
#include "TFT_eSPI.h"

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {

void Display::initScreen(TftInterface &tft)
{
    tft.fillScreen(TFT_BLACK);
}

} // namespace espgui
