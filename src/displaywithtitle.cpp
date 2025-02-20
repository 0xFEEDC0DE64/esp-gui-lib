#include "displaywithtitle.h"

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {

void DisplayWithTitle::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    m_titleLabel.start(tft);

//    tft.fillRect(0, 0, tft.width(), 35, TFT_GREY);

    tft.fillRect(0, TITLE_HEIGHT, tft.width(), TITLE_BORDER, TFT_GREY);
}

void DisplayWithTitle::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    m_titleLabel.redraw(tft, title(), TFT_GREY, TFT_BLACK, 4);
}

} // namespace espgui
