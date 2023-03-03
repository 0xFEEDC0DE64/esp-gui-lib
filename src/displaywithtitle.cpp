#include "displaywithtitle.h"

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {

void DisplayWithTitle::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    // m_titleLabel.construct(5, 5); // 230, 25
    if (!m_titleLabel)
        m_titleLabel.construct(5, 5, tft.width() - SCROLLMARGIN, 500);

    m_titleLabel->start(tft);

//    tft.fillRect(0, 0, tft.width(), 35, TFT_GREY);

    tft.fillRect(0, 34, tft.width(), 2, TFT_GREY);
}

void DisplayWithTitle::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    if (m_titleLabel)
        m_titleLabel->redraw(tft, title(), TFT_GREY, TFT_BLACK, 4);
}

} // namespace espgui
