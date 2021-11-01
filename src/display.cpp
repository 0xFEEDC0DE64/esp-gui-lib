#include "display.h"

// local includes
#include "tftinstance.h"

namespace espgui {

void Display::initScreen()
{
    tft.fillScreen(TFT_BLACK);
}

} // namespace espgui
