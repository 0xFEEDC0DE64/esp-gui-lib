#include "popupdisplay.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>

namespace espgui {

PopupDisplay::PopupDisplay(std::unique_ptr<Display> &&lastDisplay) :
    m_lastDisplay{std::move(lastDisplay)}
{
}

void PopupDisplay::initScreen()
{
    Base::initScreen();

    m_lastDisplay->initScreen();

    initOverlay();
}

void PopupDisplay::closeOverlay()
{
    auto guard = std::move(espgui::currentDisplay);
    espgui::currentDisplay = std::move(m_lastDisplay);
    espgui::currentDisplay->initScreen();
}

} // namespace espgui
