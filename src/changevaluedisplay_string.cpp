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

    m_locked = false;
}

void espgui::ChangeValueDisplay<std::string>::update()
{
    Base::update();

    m_keyboard.update();
}

void espgui::ChangeValueDisplay<std::string>::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    const auto now_ts = espchrono::millis_clock::now().time_since_epoch();
    const auto char_width = tft.textWidth(m_value, 4) / ((!m_value.empty()) ? m_value.size() : 1);
    const auto maxChars = (tft.width() - 40) / char_width;
    const auto substr_from = std::max(0U, m_value.size() < maxChars ? 0 : static_cast<int>(m_value.size()) - maxChars);
    ESP_LOGI("ChangeValueDisplay<std::string>", "str: %s, strlen: %d, maxChars: %d, tft.width(): %d, char_width: %d, substr_from: %d, textWidth(\"a\")=%d, textWidth: %d", m_value.c_str(), m_value.size(), maxChars, tft.width(), char_width, substr_from, tft.textWidth("a", 4), tft.textWidth(m_value, 4));
    const auto string = m_value.substr(substr_from);

    if (m_needsClear)
    {
        tft.drawRect(m_valueLabel.x() + tft.textWidth(*m_needsClear, 4) + 3, m_valueLabel.y(), 2, tft.fontHeight(4), TFT_BLACK);
        m_needsClear = std::nullopt;
    }

    m_valueLabel.redraw(tft, string, TFT_WHITE, TFT_BLACK, 4);

    tft.drawRect(m_valueLabel.x() + tft.textWidth(string, 4) + 3, m_valueLabel.y(), 2, tft.fontHeight(4), (now_ts % 1000ms < 500ms) ? TFT_WHITE : TFT_BLACK);

    m_keyboard.redraw(tft);

    m_locked = false;
}

void espgui::ChangeValueDisplay<std::string>::setShownValue(std::string &&value)
{
    if (m_locked)
    {
        return;
    }

    m_locked = true;

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
    if (m_locked)
    {
        return;
    }

    if (auto val = this->shownValue(); !val.empty())
    {
        val.pop_back();
        this->setShownValue(std::move(val));
    }
}
