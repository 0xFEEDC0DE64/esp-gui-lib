#include "changevaluedisplay.h"

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {
void ChangeValueDisplayInterface::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    tft.drawRoundRect(35, 65, 190, 65, 8, TFT_WHITE);
    m_valueLabel.start(tft);

    if (espgui::isLandscape(tft))
    {
        tft.drawString("Change value and press", 10, 152, TFT_WHITE, TFT_BLACK, 4);
        tft.drawString("button to confirm and", 10, 177, TFT_WHITE, TFT_BLACK, 4);
        tft.drawString("go back", 10, 202, TFT_WHITE, TFT_BLACK, 4);
    }
    else
    {
        tft.drawString("Change value and", 10, 160, TFT_WHITE, TFT_BLACK, 4);
        tft.drawString("press button to", 10, 185, TFT_WHITE, TFT_BLACK, 4);
        tft.drawString("confirm and go", 10, 210, TFT_WHITE, TFT_BLACK, 4);
        tft.drawString("back.", 10, 235, TFT_WHITE, TFT_BLACK, 4);
    }
}

template<>
void ChangeValueDisplay<float>::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    m_valueLabel.redraw(tft, fmt::format("{:.02f}", m_value), TFT_WHITE, TFT_BLACK, 7);
}
} // namespace espgui
