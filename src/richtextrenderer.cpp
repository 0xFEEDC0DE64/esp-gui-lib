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

    const uint16_t oldColor = tft.textcolor;

    int16_t width{};

again:
    if (const auto index = str.find('&'); index != std::string_view::npos)
    {
        {
            std::string_view tempStr{std::begin(str), index};
            if (!tempStr.empty())
            {
                const auto addedWith = tft.drawString(tempStr, poX, poY, font);
                poX += addedWith;
                width += addedWith;
            }
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
            {
                const auto color = [&controlChar,&oldColor](){
                    switch (controlChar)
                    {
                    case '0': return oldColor;
                    case '1': return TFT_RED;
                    case '2': return TFT_GREEN;
                    case '3': return TFT_BLUE;
                    case '4': return TFT_BLACK;
                    case '5': return TFT_WHITE;
                    case '6': return TFT_GREY;
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
//            case '&':
//            {
//                const char buf[1] = { '&' };
//                const auto addedWith = tft.drawString(std::string_view{buf, std::size(buf)}, poX, poY, font);
//                poX += addedWith;
//                width += addedWith;

//                auto newNewIter = newIter + 1;
//                if (newNewIter != std::end(str))
//                {
//                    str = std::string_view(newNewIter, std::distance(newNewIter, std::end(str)));
//                    goto again;
//                }
//                break;
//            }
            default:
            {
                const char buf[2] = { '&', controlChar };
                const auto addedWith = tft.drawString(std::string_view{buf, std::size(buf)}, poX, poY, font);
                poX += addedWith;
                width += addedWith;

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
            const auto addedWith = tft.drawString(std::string_view{buf, std::size(buf)}, poX, poY, font);
            poX += addedWith;
            width += addedWith;
        }
    }
    else if (!str.empty())
    {
        const auto addedWith = tft.drawString(str, poX, poY, font);
        poX += addedWith;
        width += addedWith;
    }

    tft.setTextColor(oldColor, tft.textbgcolor);

    return width;
}

} // namespace espgui
