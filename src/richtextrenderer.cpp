#include "richtextrenderer.h"

// system includes
#include <string_view>

// 3rdparty lib includes
#include <strutils.h>

namespace espgui {

void richTextEscape(std::string &subject)
{
    cpputils::stringReplaceAll('&', "&&", subject);
}

std::string richTextEscape(std::string_view subject)
{
    return cpputils::stringReplaceAll('&', "&&", subject);
}

int16_t renderRichText(std::string_view str, int32_t poX, int32_t poY)
{
    return renderRichText(str, poX, poY, tft.textfont);
}

int16_t renderRichText(std::string_view str, int32_t poX, int32_t poY, uint8_t font)
{
    if (str.empty())
        return 0;

    const int16_t fontHeight = tft.fontHeight(font);

    const uint8_t oldFont = font;
    const uint16_t oldColor = tft.textcolor;

    int16_t width{};

    const auto drawString = [&poX, &poY, &font, &width, &fontHeight, &oldFont](std::string_view str) {
        const auto addedWith = tft.drawString(str, poX, poY, font);

        if (font != oldFont)
        {
            if (const int16_t newFontHeight = tft.fontHeight(font); newFontHeight < fontHeight)
            {
                tft.fillRect(poX, poY + newFontHeight,
                             addedWith, fontHeight - newFontHeight,
                             tft.textbgcolor);
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
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            {
                const auto color = [&controlChar,&oldColor](){
                    switch (controlChar)
                    {
                    case '0': return oldColor;
                    case '1': return TFT_RED;
                    case '2': return TFT_GREEN;
                    case '3': return TFT_BLUE;
                    case '4': return TFT_YELLOW;
                    case '5': return TFT_BLACK;
                    case '6': return TFT_WHITE;
                    case '7': return TFT_GREY;
                    }
                    __builtin_unreachable();
                }();

                tft.setTextColor(color, tft.textbgcolor);

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
            case 'm':
            {
                font = [&controlChar,&oldFont]() -> uint8_t {
                    switch (controlChar)
                    {
                    case 'f': return oldFont;
                    case 's': return 2;
                    case 'm': return 4;
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

    tft.setTextColor(oldColor, tft.textbgcolor);

    return width;
}

} // namespace espgui
