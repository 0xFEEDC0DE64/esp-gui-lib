#include "changevaluedisplay_string.h"

// local includes
#include "tftinstance.h"

void espgui::ChangeValueDisplay<std::string>::start()
{
    Base::start();

    m_value = /*static_cast<AccessorInterface<std::string>*>*/(this)->getValue();

    m_pressed = false;
}

void espgui::ChangeValueDisplay<std::string>::initScreen()
{
    Base::initScreen();

    tft.drawRect(25, 75, 190, 65, TFT_WHITE);
    m_valueLabel.start();

    tft.setTextFont(4);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Change value and", 10, 160);
    tft.drawString("press button to", 10, 185);
    tft.drawString("confirm and go", 10, 210);
    tft.drawString("back.", 10, 235);
}

void espgui::ChangeValueDisplay<std::string>::update()
{
    Base::update();

    if (m_pressed)
    {
        m_pressed = false;
        if (auto result = /*static_cast<AccessorInterface<std::string>*>*/(this)->setValue(m_value); result)
            confirm();
        else
            errorOccured(std::move(result).error());
    }
}

void espgui::ChangeValueDisplay<std::string>::redraw()
{
    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(4);
    m_valueLabel.redraw(m_value);
}

void espgui::ChangeValueDisplay<std::string>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Left: this->back(); break;
    case Button::Right: m_pressed = true; break;
    default:;
    }
}
