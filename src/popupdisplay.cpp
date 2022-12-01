#include "popupdisplay.h"

// 3rdparty lib includes
#include <screenmanager.h>

namespace espgui {

PopupDisplay::PopupDisplay(std::unique_ptr<Display> &&lastDisplay) :
    m_lastDisplay{std::move(lastDisplay)}
{
}

void PopupDisplay::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    m_lastDisplay->initScreen(tft);

    initOverlay(tft);
}

void PopupDisplay::redraw(TftInterface &tft)
{
    if (m_wantsClose)
        closeOverlay(tft);
    else
        Base::redraw(tft);
}

void PopupDisplay::closeOverlay()
{
    m_wantsClose = true;
}

void PopupDisplay::closeOverlay(TftInterface &tft)
{
    auto guard = std::move(espgui::currentDisplay);
    espgui::currentDisplay = std::move(m_lastDisplay);
    espgui::currentDisplay->initScreen(tft);
}

} // namespace espgui
