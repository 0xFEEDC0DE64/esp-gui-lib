#pragma once

// system includes
#include <type_traits>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "displaywithtitle.h"
#include "textinterface.h"
#include "confirminterface.h"
#include "backinterface.h"
#include "errorhandlerinterface.h"
#include "accessorinterface.h"
#include "widgets/label.h"
#include "tftinstance.h"

namespace espgui {

class ChangeValueDisplayInterface :
    public DisplayWithTitle,
    public virtual ConfirmInterface,
    public virtual BackInterface,
    public virtual ErrorHandlerInterface
{
    using Base = DisplayWithTitle;

public:
    void initScreen() override;

    ChangeValueDisplayInterface *asChangeValueDisplayInterface() override { return this; }
    const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const override { return this; }

    virtual int shownValue() const = 0;
    virtual void setShownValue(int value) = 0;

protected:
    Label m_valueLabel{36, 71}; // 188, 53
};

template<typename Tvalue>
class ChangeValueDisplaySettingsInterface
{
public:
    virtual Tvalue step() const { return 1; };
};

template<typename Tvalue, typename Tratio>
class RatioNumberStep : public virtual ChangeValueDisplaySettingsInterface<Tvalue>
{
public:
    Tvalue step() const override { return Tvalue(Tratio::num) / Tratio::den; }
};

template<typename Tvalue>
class ChangeValueDisplay :
    public ChangeValueDisplayInterface,
    public virtual AccessorInterface<Tvalue>,
    public virtual ChangeValueDisplaySettingsInterface<Tvalue>
{
    using Base = ChangeValueDisplayInterface;

    static_assert((std::is_integral_v<Tvalue> || std::is_floating_point_v<Tvalue>) && !std::is_same_v<Tvalue, bool>);

public:
    void start() override;
    void update() override;
    void redraw() override;

    void buttonPressed(Button button) override;
    void buttonReleased(Button button) override;

    int shownValue() const { return m_value; }
    void setShownValue(int value) { m_value = value; }

private:
    Tvalue m_value{};

    int m_rotateOffset;
    bool m_pressed{};

    struct ButtonHeldInfo
    {
        espchrono::millis_clock::time_point nextTimestamp;
        int counter{};
    };

    std::optional<ButtonHeldInfo> m_upHeld;
    std::optional<ButtonHeldInfo> m_downHeld;
};

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::start()
{
    Base::start();

    m_value = this->getValue();

    m_rotateOffset = 0;
    m_pressed = false;

    m_upHeld = std::nullopt;
    m_downHeld = std::nullopt;
}

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::update()
{
    Base::update();

    const auto now = espchrono::millis_clock::now();
    if (m_upHeld && now >= m_upHeld->nextTimestamp)
    {
        using namespace std::chrono_literals;
        m_upHeld->nextTimestamp += m_upHeld->counter > 10 ? 50ms : (m_upHeld->counter > 3 ? 100ms : 200ms);
        m_upHeld->counter++;
        m_rotateOffset--;
    }
    if (m_downHeld && now >= m_downHeld->nextTimestamp)
    {
        using namespace std::chrono_literals;
        m_downHeld->nextTimestamp += m_downHeld->counter > 10 ? 50ms : (m_downHeld->counter > 3 ? 100ms : 200ms);
        m_downHeld->counter++;
        m_rotateOffset++;
    }

    {
        const auto rotateOffset = m_rotateOffset;
        m_rotateOffset = 0;

        m_value -= rotateOffset * this->step();
    }

    if (m_pressed)
    {
        m_pressed = false;
        if (auto result = static_cast<AccessorInterface<Tvalue>*>(this)->setValue(m_value); result)
            confirm();
        else
            errorOccurred(std::move(result).error());
    }
}

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::redraw()
{
    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(7);
    m_valueLabel.redraw(std::to_string(m_value));
}

template<>
void ChangeValueDisplay<float>::redraw();

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Left: this->back(); break;
    case Button::Right: m_pressed = true; break;
    using namespace std::chrono_literals;
    case Button::Up:
        m_rotateOffset--;
        m_upHeld = ButtonHeldInfo { .nextTimestamp = espchrono::millis_clock::now() + 300ms };
        break;
    case Button::Down:
        m_rotateOffset++;
        m_downHeld = ButtonHeldInfo { .nextTimestamp = espchrono::millis_clock::now() + 300ms };
        break;
    }
}

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::buttonReleased(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Up:
        m_upHeld = std::nullopt;
        break;
    case Button::Down:
        m_downHeld = std::nullopt;
        break;
    default:;
    }
}

} // namespace espgui
