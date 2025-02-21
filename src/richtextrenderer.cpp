#include "richtextrenderer.h"

// system includes
#include <string_view>

// 3rdparty lib includes
#include <fontrenderer.h>

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {

int16_t renderRichText(TftInterface &tft, std::string_view str, int32_t poX, int32_t poY, uint16_t color, uint16_t bgcolor, uint8_t font)
{
    FontRenderer fontRenderer{tft};
    return renderRichText(tft, fontRenderer, str, poX, poY, color, bgcolor, font);
}

int16_t renderRichText(TftInterface &tft, FontRenderer &fontRenderer, std::string_view str, int32_t poX, int32_t poY, uint16_t color, uint16_t bgcolor, uint8_t font)
{
    if (str.empty())
        return 0;

    const int16_t fontHeight = fontRenderer.fontHeight(font);

    const uint16_t oldColor = color;
    const uint8_t oldFont = font;

    int16_t width{};

    const auto drawString = [&tft, &fontRenderer, &poX, &poY, &color, &bgcolor, &font, &width, &fontHeight, &oldFont](std::string_view str) {
        const auto addedWith = fontRenderer.drawString(str, poX, poY, color, bgcolor, font);

        if (font != oldFont)
        {
            if (const int16_t newFontHeight = fontRenderer.fontHeight(font); newFontHeight < fontHeight)
            {
                tft.fillRect(poX, poY + newFontHeight,
                             addedWith, fontHeight - newFontHeight,
                             bgcolor);
            }
        }

        poX += addedWith;
        width += addedWith;
    };

again:
    if (const auto index = str.find('&'); index != std::string_view::npos)
    {
        {
            std::string_view tempStr{std::begin(str), index};
            if (!tempStr.empty())
                drawString(tempStr);
        }

        auto newIter = std::begin(str) + index + 1;
        if (newIter != std::end(str))
        {
            switch (const auto controlChar = *newIter)
            {
            case 'c':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                color = [&controlChar,&oldColor](){
                    switch (controlChar)
                    {
                    case 'c': return oldColor;
                    case '1': return TFT_RED;
                    case '2': return TFT_GREEN;
                    case '3': return TFT_NICEBLUE;
                    case '4': return TFT_YELLOW;
                    case '5': return TFT_BLACK;
                    case '6': return TFT_WHITE;
                    case '7': return TFT_GREY;
                    case '8': return TFT_PURPLE;
                    case '9': return TFT_BROWN;
                    }
                    __builtin_unreachable();
                }();

                auto newNewIter = newIter + 1;
                if (newNewIter != std::end(str))
                {
                    str = std::string_view(newNewIter, std::distance(newNewIter, std::end(str)));
                    goto again;
                }
                break;
            }
            case 'f':
            case 's':
            case 'S':
            case 'm':
            {
                bool changeHeight = false;
                font = [&controlChar,&oldFont,&changeHeight]() -> uint8_t {
                    switch (controlChar)
                    {
                    case 'f': return oldFont;
                    case 's': return 2;
                    case 'S': {
                        changeHeight = true;
                        return 2;
                    }
                    case 'm': return 4;
                    }
                    __builtin_unreachable();
                }();

                if (changeHeight)
                {
                    // adjust y rendering position to new font height
                    poY += fontRenderer.fontHeight(oldFont) - fontRenderer.fontHeight(font);
                }

                auto newNewIter = newIter + 1;
                if (newNewIter != std::end(str))
                {
                    str = std::string_view(newNewIter, std::distance(newNewIter, std::end(str)));
                    goto again;
                }
                break;
            }
            default:
            {
                const char buf[2] = { '&', controlChar };
                drawString(std::string_view{buf, std::size(buf)});

                auto newNewIter = newIter + 1;
                if (newNewIter != std::end(str))
                {
                    str = std::string_view(newNewIter, std::distance(newNewIter, std::end(str)));
                    goto again;
                }
                break;
            }
            }
        }
        else
        {
            const char buf[1] = { '&' };
            drawString(std::string_view{buf, std::size(buf)});
        }
    }
    else if (!str.empty())
    {
        drawString(str);
    }

    return width;
}

} // namespace espgui
