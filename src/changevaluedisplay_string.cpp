#include "changevaluedisplay_string.h"

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

using namespace std::chrono_literals;

void espgui::ChangeValueDisplay<std::string>::start()
{
    Base::start();

    m_value = this->getValue();
}

void espgui::ChangeValueDisplay<std::string>::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    tft.drawRoundRect(10, 50, tft.width() - 20, 34, 5, TFT_WHITE);
    m_valueLabel.start(tft);

    m_keyboard.start(tft);

    m_needsClear = std::nullopt;
}

void espgui::ChangeValueDisplay<std::string>::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    const auto now_ts = espchrono::millis_clock::now().time_since_epoch();
    const auto char_width = tft.textWidth("A", 4);
    const auto maxChars = (tft.width() - 20) / char_width;
    const auto string = m_value.substr(std::max(0, static_cast<int>(m_value.size()) - maxChars));

    m_valueLabel.redraw(tft, string, TFT_WHITE, TFT_BLACK, 4);

    if (m_needsClear)
    {
        tft.drawRect(m_valueLabel.x() + tft.textWidth(*m_needsClear, 4) + 3, m_valueLabel.y(), 2, tft.fontHeight(4), TFT_BLACK);
        m_needsClear = std::nullopt;
    }

    // tft.drawRect(m_valueLabel.x() + tft.textWidth(m_value, 4) + 3, m_valueLabel.y(), 2, tft.fontHeight(4), (now % 1000 < 500) ? TFT_WHITE : TFT_BLACK);
    tft.drawRect(m_valueLabel.x() + tft.textWidth(string, 4) + 3, m_valueLabel.y(), 2, tft.fontHeight(4), (now_ts % 1000ms < 500ms) ? TFT_WHITE : TFT_BLACK);

    m_keyboard.redraw(tft);
}

void espgui::ChangeValueDisplay<std::string>::setShownValue(std::string &&value)
{
    m_needsClear = std::move(m_value);
    m_value = std::move(value);
}

void espgui::ChangeValueDisplay<std::string>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);
    m_keyboard.buttonPressed(button);
}

void espgui::ChangeValueDisplay<std::string>::buttonReleased(Button button)
{
    //Base::buttonReleased(button);
    m_keyboard.buttonReleased(button);
    // TODO stop auto scroll
}

void espgui::ChangeValueDisplay<std::string>::confirmValue()
{
    if (auto result = this->setValue(m_value); result)
        confirm();
    else
        errorOccurred(std::move(result).error());
}

void espgui::ChangeValueDisplay<std::string>::removeLastCharFromShownValue()
{
    if (auto val = this->shownValue(); !val.empty())
    {
        val.pop_back();
        this->setShownValue(std::move(val));
    }
}
