#include "changevaluedisplay.h"

// 3rdparty lib includes
#include <fmt/core.h>

namespace espgui {
void ChangeValueDisplayInterface::initScreen()
{
    Base::initScreen();

    tft.drawRect(25, 75, 190, 65, TFT_WHITE);
    m_valueLabel.start();

    tft.setTextFont(4);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Change value and", 10, 160);
    tft.drawString("press button to", 10, 185);
    tft.drawString("confirm and go", 10, 210);
    tft.drawString("back.", 10, 235);
}

template<>
void ChangeValueDisplay<float>::redraw()
{
    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(7);
    m_valueLabel.redraw(fmt::format("{:.02f}", m_value));
}
} // namespace espgui
