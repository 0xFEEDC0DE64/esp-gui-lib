#include "displaywithtitle.h"

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {

void DisplayWithTitle::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    m_titleLabel.start(tft);
    tft.fillRect(0, 33, tft.width(), 3, TFT_WHITE);
}

void DisplayWithTitle::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    m_titleLabel.redraw(tft, text(), TFT_YELLOW, TFT_BLACK, 4);
}

} // namespace espgui
