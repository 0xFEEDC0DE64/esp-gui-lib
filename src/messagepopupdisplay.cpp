#include "messagepopupdisplay.h"

// system includes
#include <string_view>

// 3rdparty lib includes
#include <screenmanager.h>
#include <cppmacros.h>
#include <fontrenderer.h>

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

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

void MessagePopupDisplay::initOverlay(TftInterface &tft)
{
    FontRenderer fontRenderer{tft};

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

    int x = leftMargin + 5;
    int y = topMargin + 5;

    for (char c : m_message)
    {
        if (c == '\n' || x > tft.width() - rightMargin - 10)
        {
            x = leftMargin + 5;
            y += fontRenderer.fontHeight(4);
        }

        if (c != '\n')
        {
            const auto addedWidth = fontRenderer.drawString(std::string_view{&c, 1}, x, y, TFT_WHITE, color565(30, 30, 30), 4);
            x += addedWidth;
        }

        if (y >= tft.height() - bottomMargin)
            break;
    }

    if constexpr (false)
    {
        tft.drawSunkenRect(leftMargin + 15, bottom - 40,
                                   (width - 15 - 10 - 15) / 2,
                                   30,
                                   color565(240, 240, 240),
                                   color565(100, 100, 100),
                                   color565(170, 170, 170));

        fontRenderer.drawString("Retry", leftMargin + 18, bottom - 37, TFT_BLACK, color565(170, 170, 170), 4);
    }

    tft.drawSunkenRect(leftMargin + 15 + ((width - 15 - 30 - 15) / 2) + 15, bottom - 40,
                               (width - 15 - 10 - 15) / 2,
                               30,
                               color565(240, 240, 240),
                               color565(100, 100, 100),
                               color565(170, 170, 170));

    fontRenderer.drawString("Ok", leftMargin + 18 + ((width - 15 - 30 - 15) / 2) + 15 + 1, bottom - 37, TFT_BLACK, color565(170, 170, 170), 4);
}

} // namespace espgui
