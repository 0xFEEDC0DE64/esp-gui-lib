#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <espchrono.h>
#include <fontrenderer.h>

// local includes
#include "changevaluedisplay.h"
#include "tftinterface.h"
#include "tftcolors.h"
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
    void initScreen(TftInterface &tft) override;
    void update() override;
    void redraw(TftInterface &tft) override;

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
void ChangeValueDisplayChrono<T>::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    FontRenderer fontRenderer{tft};

    tft.drawRoundRect(32, 65, 190, 34, 8, TFT_WHITE);
    m_valueLabel.start(tft);

    if (espgui::isLandscape(tft))
    {
        fontRenderer.drawString("Change value and press", 10, 152, TFT_WHITE, TFT_BLACK, 4);
        fontRenderer.drawString("button to confirm and", 10, 177, TFT_WHITE, TFT_BLACK, 4);
        fontRenderer.drawString("go back", 10, 202, TFT_WHITE, TFT_BLACK, 4);
    }
    else
    {
        fontRenderer.drawString("Change value and", 10, 160, TFT_WHITE, TFT_BLACK, 4);
        fontRenderer.drawString("press button to", 10, 185, TFT_WHITE, TFT_BLACK, 4);
        fontRenderer.drawString("confirm and go", 10, 210, TFT_WHITE, TFT_BLACK, 4);
        fontRenderer.drawString("back.", 10, 235, TFT_WHITE, TFT_BLACK, 4);
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
            errorOccurred(std::move(result).error());
    }
}

template<typename T>
void ChangeValueDisplayChrono<T>::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    m_valueLabel.redraw(tft, espchrono::toString(m_value), TFT_WHITE, TFT_BLACK, 4);
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
