#include "displaywithtitle.h"

// local includes
#include "tftinstance.h"

namespace espgui {

void DisplayWithTitle::initScreen()
{
    Base::initScreen();

    m_titleLabel.start();
    tft.fillRect(0, 33, tft.width(), 3, TFT_WHITE);
}

void DisplayWithTitle::redraw()
{
    Base::redraw();

    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw(text());
}

} // namespace espgui
