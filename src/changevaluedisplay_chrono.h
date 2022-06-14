#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "changevaluedisplay.h"
#include "displaywithtitle.h"
#include "confirminterface.h"
#include "backinterface.h"
#include "errorhandlerinterface.h"
#include "widgets/label.h"

namespace espgui {

namespace detail {
template<typename T>
class ChangeValueDisplayChrono :
    public DisplayWithTitle,
    public virtual AccessorInterface<T>,
    public virtual ConfirmInterface,
    public virtual BackInterface,
    public virtual ErrorHandlerInterface
{
    using Base = DisplayWithTitle;

public:
    void start() override;
    void initScreen() override;
    void update() override;
    void redraw() override;

    void buttonPressed(Button button) override;
    void buttonReleased(Button button) override;

private:
    T m_value;
    bool m_pressed{};

    Label m_valueLabel{36, 71}; // 188, 53
};

template<typename T>
void ChangeValueDisplayChrono<T>::start()
{
    Base::start();

    m_value = this->getValue();

    m_pressed = false;
}

template<typename T>
void ChangeValueDisplayChrono<T>::initScreen()
{
    Base::initScreen();

    tft.drawRoundRect(32, 65, 190, 34, 8, TFT_WHITE);
    m_valueLabel.start();

    tft.setTextFont(4);
    tft.setTextColor(TFT_WHITE);
    if (espgui::isLandscape())
    {
        tft.drawString("Change value and press", 10, 152);
        tft.drawString("button to confirm and", 10, 177);
        tft.drawString("go back", 10, 202);
    }
    else
    {
        tft.drawString("Change value and", 10, 160);
        tft.drawString("press button to", 10, 185);
        tft.drawString("confirm and go", 10, 210);
        tft.drawString("back.", 10, 235);
    }
}

template<typename T>
void ChangeValueDisplayChrono<T>::update()
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

template<typename T>
void ChangeValueDisplayChrono<T>::redraw()
{
    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(4);
    m_valueLabel.redraw(espchrono::toString(m_value));
}

template<typename T>
void ChangeValueDisplayChrono<T>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Left: this->back(); break;
    case Button::Right: m_pressed = true; break;
    case Button::Up: m_value += T{1}; break;
    case Button::Down: m_value -= T{1}; break;
    default:;
    }
}

template<typename T>
void ChangeValueDisplayChrono<T>::buttonReleased(Button button)
{
    //Base::buttonPressed(button);

    // TODO stop auto scroll
}

} // namespace detail

template<>
class ChangeValueDisplay<espchrono::hours32> : public detail::ChangeValueDisplayChrono<espchrono::hours32> {};
template<>
class ChangeValueDisplay<espchrono::minutes32> : public detail::ChangeValueDisplayChrono<espchrono::minutes32> {};
template<>
class ChangeValueDisplay<espchrono::seconds32> : public detail::ChangeValueDisplayChrono<espchrono::seconds32> {};
template<>
class ChangeValueDisplay<espchrono::milliseconds32> : public detail::ChangeValueDisplayChrono<espchrono::milliseconds32> {};

} // namespace espgui
