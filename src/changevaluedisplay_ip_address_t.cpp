#include "changevaluedisplay_ip_address_t.h"

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {

void ChangeValueDisplay<wifi_stack::ip_address_t>::start()
{
    Base::start();

    m_value = this->getValue();

    m_currentIndex = 0;
}

void ChangeValueDisplay<wifi_stack::ip_address_t>::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    tft.drawString("Change IP Address", 0, 50, TFT_WHITE, TFT_BLACK, 4);

    for(int i = 0; i <= 3; i++)
    {
        drawRect(tft, i, 3, TFT_WHITE);
        drawRect(tft, i, 4, TFT_WHITE);
    }

    for (auto &label : m_labels)
        label.start(tft);

    tft.drawString(".", spacing+boxWidth+spacing/4, y, TFT_WHITE, TFT_BLACK, 4);
    tft.drawString(".", spacing*2+boxWidth*2+spacing/4, y, TFT_WHITE, TFT_BLACK, 4);
    tft.drawString(".", spacing*3+boxWidth*3+spacing/4, y, TFT_WHITE, TFT_BLACK, 4);

    drawRect(tft, m_currentIndex, 1, TFT_YELLOW);
    drawRect(tft, m_currentIndex, 2, TFT_YELLOW);

    m_lastIndex = m_currentIndex;
}

void ChangeValueDisplay<wifi_stack::ip_address_t>::update()
{
    Base::update();

    // TODO auto scroll
}

void ChangeValueDisplay<wifi_stack::ip_address_t>::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    if (m_lastIndex != m_currentIndex)
    {
        drawRect(tft, m_lastIndex, 1, TFT_BLACK);
        drawRect(tft, m_lastIndex, 2, TFT_BLACK);

        drawRect(tft, m_currentIndex, 1, TFT_YELLOW);
        drawRect(tft, m_currentIndex, 2, TFT_YELLOW);

        m_lastIndex = m_currentIndex;
    }

    for (auto i = 0; i < 4; i++)
        m_labels[i].redraw(tft, std::to_string(m_value.bytes()[i]), TFT_WHITE, TFT_BLACK, 4);
}

void ChangeValueDisplay<wifi_stack::ip_address_t>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Left:
        if (m_currentIndex > 0)
            m_currentIndex--;
        else
            back();
        break;
    case Button::Right:
        if (m_currentIndex < 3)
            m_currentIndex++;
        else
        {
            if (auto result = this->setValue(m_value); result)
                confirm();
            else
                errorOccurred(std::move(result).error());
        }
        break;
    case Button::Up:
        m_value.bytes()[m_currentIndex]++;
        break;
    case Button::Down:
        m_value.bytes()[m_currentIndex]--;
        break;
    default:;
    }
}

void ChangeValueDisplay<wifi_stack::ip_address_t>::buttonReleased(Button button)
{
    //Base::buttonReleased(button);

    // TODO stop auto scroll
}

void ChangeValueDisplay<wifi_stack::ip_address_t>::drawRect(TftInterface &tft, int index, int offset, uint32_t color) const
{
    tft.drawRoundRect(m_labels[index].x()-offset, m_labels[index].y()-offset, boxWidth+(offset*2), boxHeight+(offset*2), 3, color);
}

} // namespace espgui
