#include "changevaluedisplay_ip_address_t.h"

// local includes
#include "tftinstance.h"

void espgui::ChangeValueDisplay<wifi_stack::ip_address_t>::start()
{
    Base::start();

    m_value = this->getValue();

    m_pressed = false;
}

void espgui::ChangeValueDisplay<wifi_stack::ip_address_t>::initScreen()
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

void espgui::ChangeValueDisplay<wifi_stack::ip_address_t>::update()
{
    Base::update();

    if (m_pressed)
    {
        m_pressed = false;
        if (auto result = this->setValue(m_value); result)
            confirm();
        else
            errorOccured(std::move(result).error());
    }
}

void espgui::ChangeValueDisplay<wifi_stack::ip_address_t>::redraw()
{
    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(4);
    m_valueLabel.redraw(wifi_stack::toString(m_value));
}

void espgui::ChangeValueDisplay<wifi_stack::ip_address_t>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Left: this->back(); break;
    case Button::Right: m_pressed = true; break;
    default:;
    }
}

void espgui::ChangeValueDisplay<wifi_stack::ip_address_t>::buttonReleased(Button button)
{
    //Base::buttonReleased(button);

    // TODO stop auto scroll
}
