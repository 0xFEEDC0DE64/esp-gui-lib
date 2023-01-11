#include "displaywithtitle.h"

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {

void DisplayWithTitle::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    m_titleLabel.start(tft);

    tft.fillRect(0, 0, tft.width(), 35, TFT_GREY);

//    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);
}

void DisplayWithTitle::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    m_titleLabel.redraw(tft, title(), TFT_WHITE, TFT_GREY, 4);
}

} // namespace espgui
