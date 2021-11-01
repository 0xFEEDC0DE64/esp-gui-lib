#pragma once

// local includes
#include "displaywithtitle.h"
#include "textinterface.h"
#include "actioninterface.h"
#include "accessorinterface.h"
#include "widgets/label.h"
#include "tftinstance.h"

namespace espgui {
class ChangeValueDisplayInterface :
    public DisplayWithTitle,
    public virtual ActionInterface
{
    using Base = DisplayWithTitle;
public:
    void initScreen() override;

    ChangeValueDisplayInterface *asChangeValueDisplayInterface() override { return this; }
    const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const override { return this; }

    virtual int shownValue() const = 0;
    virtual void setShownValue(int value) = 0;

protected:
    Label m_valueLabel{26, 81}; // 188, 53
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

public:
    void start() override;
    void update() override;
    void redraw() override;

    void rotate(int offset) override;
    void confirm() override;

    int shownValue() const { return m_value; }
    void setShownValue(int value) { m_value = value; }

private:
    Tvalue m_value{};

    int m_rotateOffset;
    bool m_pressed{};
};

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::start()
{
    m_value = static_cast<AccessorInterface<Tvalue>*>(this)->getValue();

    m_rotateOffset = 0;
    m_pressed = false;
}

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::update()
{
    Base::update();

    if (!m_pressed)
    {
        const auto rotateOffset = m_rotateOffset;
        m_rotateOffset = 0;

        m_value -= rotateOffset * static_cast<ChangeValueDisplaySettingsInterface<Tvalue>*>(this)->step();
    }
    else
    {
        static_cast<AccessorInterface<Tvalue>*>(this)->setValue(m_value);
        triggered();
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
void ChangeValueDisplay<Tvalue>::rotate(int offset)
{
    m_rotateOffset += offset;
}

template<typename Tvalue>
void ChangeValueDisplay<Tvalue>::confirm()
{
    m_pressed = true;
}
} // namespace espgui
