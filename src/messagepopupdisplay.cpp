#include "messagepopupdisplay.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>
#include <cppmacros.h>

namespace espgui {

MessagePopupDisplay::MessagePopupDisplay(std::string &&message, std::unique_ptr<Display> &&lastDisplay) :
    PopupDisplay{std::move(lastDisplay)},
    m_message{std::move(message)}
{
}

void MessagePopupDisplay::buttonPressed(Button button)
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

void MessagePopupDisplay::initOverlay()
{
    const auto leftMargin = 20;
    const auto rightMargin = leftMargin;
    const auto topMargin = tft.height() > 300 ? 50 : 20;
    const auto bottomMargin = topMargin;

    const auto width = tft.width() - leftMargin - rightMargin;
    const auto height = tft.height() - topMargin - bottomMargin;
    const auto right = tft.width() - rightMargin;
    const auto bottom = tft.height() - bottomMargin;

    CPP_UNUSED(right)

    tft.drawSunkenRect(leftMargin, topMargin, width, height,
                               color565(240, 240, 240),
                               color565(100, 100, 100),
                               color565(30, 30, 30));

    tft.setTextColor(TFT_WHITE, color565(30, 30, 30));

    int x = leftMargin + 5;
    int y = topMargin + 5;
    for (char c : m_message)
    {
        if (c == '\n' || x > tft.width() - rightMargin - 10)
        {
            x = leftMargin + 5;
            y += tft.fontHeight(4);
        }

        if (c != '\n')
        {
            const auto addedWidth = tft.drawChar(tft.decodeUTF8(c), x, y, 4);
            x += addedWidth;
        }

        if (y >= tft.height() - bottomMargin)
            break;
    }

    tft.setTextColor(TFT_BLACK, color565(170, 170, 170));

    if constexpr (false)
    {
        tft.drawSunkenRect(leftMargin + 15, bottom - 40,
                                   (width - 15 - 10 - 15) / 2,
                                   30,
                                   color565(240, 240, 240),
                                   color565(100, 100, 100),
                                   color565(170, 170, 170));

        tft.drawString("Retry", leftMargin + 18, bottom - 37);
    }

    tft.drawSunkenRect(leftMargin + 15 + ((width - 15 - 30 - 15) / 2) + 15, bottom - 40,
                               (width - 15 - 10 - 15) / 2,
                               30,
                               color565(240, 240, 240),
                               color565(100, 100, 100),
                               color565(170, 170, 170));

    tft.drawString("Ok", leftMargin + 18 + ((width - 15 - 30 - 15) / 2) + 15 + 1, bottom - 37);
}

} // namespace espgui
