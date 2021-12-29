#include "popupdisplay.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>
#include <cppmacros.h>

namespace espgui {

PopupDisplay::PopupDisplay(std::string &&message, std::unique_ptr<Display> &&lastDisplay) :
    m_message{std::move(message)}, m_lastDisplay{std::move(lastDisplay)}
{
}

void PopupDisplay::initScreen()
{
    Base::initScreen();

    m_lastDisplay->initScreen();

    initOverlay();
}

void PopupDisplay::buttonPressed(espgui::Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    using espgui::Button;
    case Button::Left:
    case Button::Right:
        closeOverlay();
        break;
    default:;
    }
}

void PopupDisplay::initOverlay()
{
    constexpr auto leftMargin = 20;
    constexpr auto rightMargin = leftMargin;
    constexpr auto topMargin = 50;
    constexpr auto bottomMargin = topMargin;

    const auto width = espgui::tft.width() - leftMargin - rightMargin;
    const auto height = espgui::tft.height() - topMargin - bottomMargin;
    const auto right = espgui::tft.width() - rightMargin;
    const auto bottom = espgui::tft.height() - bottomMargin;

    CPP_UNUSED(right)

    espgui::tft.drawSunkenRect(leftMargin, topMargin, width, height,
                               color565(240, 240, 240),
                               color565(100, 100, 100),
                               color565(30, 30, 30));

    espgui::tft.setTextColor(TFT_WHITE, color565(30, 30, 30));

    int x = leftMargin + 5;
    int y = topMargin + 5;
    for (char c : m_message)
    {
        if (c == '\n' || x > espgui::tft.width() - rightMargin - 10)
        {
            x = leftMargin + 5;
            y += espgui::tft.fontHeight(4);
        }

        if (c != '\n')
        {
            const auto addedWidth = espgui::tft.drawChar(espgui::tft.decodeUTF8(c), x, y, 4);
            x += addedWidth;
        }

        if (y >= espgui::tft.height() - bottomMargin)
            break;
    }

    espgui::tft.setTextColor(TFT_BLACK, color565(170, 170, 170));

    if constexpr (false)
    {
        espgui::tft.drawSunkenRect(leftMargin + 15, bottom - 40,
                                   (width - 15 - 10 - 15) / 2,
                                   30,
                                   color565(240, 240, 240),
                                   color565(100, 100, 100),
                                   color565(170, 170, 170));

        espgui::tft.drawString("Retry", leftMargin + 18, bottom - 37);
    }

    espgui::tft.drawSunkenRect(leftMargin + 15 + ((width - 15 - 30 - 15) / 2) + 15, bottom - 40,
                               (width - 15 - 10 - 15) / 2,
                               30,
                               color565(240, 240, 240),
                               color565(100, 100, 100),
                               color565(170, 170, 170));

    espgui::tft.drawString("Ok", leftMargin + 18 + ((width - 15 - 30 - 15) / 2) + 15 + 1, bottom - 37);
}

void PopupDisplay::closeOverlay()
{
    auto guard = std::move(espgui::currentDisplay);
    espgui::currentDisplay = std::move(m_lastDisplay);
    espgui::currentDisplay->initScreen();
}

} // namespace espgui
