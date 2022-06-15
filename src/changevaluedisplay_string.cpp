#include "changevaluedisplay_string.h"

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "tftinstance.h"

void espgui::ChangeValueDisplay<std::string>::start()
{
    Base::start();

    m_value = this->getValue();
}

void espgui::ChangeValueDisplay<std::string>::initScreen()
{
    Base::initScreen();

    tft.drawRoundRect(10, 50, tft.width() - 20, 34, 5, TFT_WHITE);
    m_valueLabel.start();

    m_keyboard.start();
}

void espgui::ChangeValueDisplay<std::string>::redraw()
{
    const auto now = espchrono::millis_clock::now().time_since_epoch().count() / 1000;
    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(4);
    m_valueLabel.redraw(m_value);

    tft.drawRect(m_valueLabel.x() + tft.textWidth(m_value) + 3, m_valueLabel.y(), 2, tft.fontHeight(), (now % 1000 < 500) ? TFT_WHITE : TFT_BLACK);
}

void espgui::ChangeValueDisplay<std::string>::setShownValue(std::string &&value)
{
    tft.drawRect(m_valueLabel.x() + tft.textWidth(m_value) + 3, m_valueLabel.y(), 2, tft.fontHeight(), TFT_BLACK);
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
