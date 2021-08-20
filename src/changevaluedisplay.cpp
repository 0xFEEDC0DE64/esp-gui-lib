#include "changevaluedisplay.h"

namespace espgui {
void ChangeValueDisplayInterface::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

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
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);
    m_titleLabel.redraw(text());

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(7);
    m_valueLabel.redraw(fmt::format("{:.02f}", m_value));
}
} // namespace espgui
