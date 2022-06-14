#include "changevaluedisplay.h"

// 3rdparty lib includes
#include <fmt/core.h>

namespace espgui {
void ChangeValueDisplayInterface::initScreen()
{
    Base::initScreen();

    tft.drawRoundRect(35, 65, 190, 65, 8, TFT_WHITE);
    m_valueLabel.start();

    tft.setTextFont(4);
    tft.setTextColor(TFT_WHITE);
    if (espgui::isLandscape())
    {
        tft.drawString("Change value and press", 10, 152);
        tft.drawString("button to confirm and", 10, 177);
        tft.drawString("go back", 10, 202);
    }
    else
    {
        tft.drawString("Change value and", 10, 160);
        tft.drawString("press button to", 10, 185);
        tft.drawString("confirm and go", 10, 210);
        tft.drawString("back.", 10, 235);
    }
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
