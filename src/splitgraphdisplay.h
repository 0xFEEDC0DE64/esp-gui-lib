#pragma once

// local includes
#include "display.h"
#include "tftinterface.h"
#include "tftcolors.h"
#include "titleinterface.h"
#include "widgets/label.h"
#include "widgets/graph.h"
#include "confirminterface.h"
#include "backinterface.h"

namespace espgui {

template<std::size_t COUNT>
class TopGraphAccessorInterface
{
public:
    virtual typename Graph<200, COUNT>::Container getTopBuffers() const = 0;
};

template<typename T>
class SingleTopGraphAccessor : public virtual TopGraphAccessorInterface<1>
{
public:
    typename Graph<200, 1>::Container getTopBuffers() const override
    {
        return {T{}.getBuffer()};
    }
};

template<std::size_t COUNT>
class BottomGraphAccessorInterface
{
public:
    virtual typename Graph<200, COUNT>::Container getBottomBuffers() const = 0;
};

template<typename T>
class SingleBottomGraphAccessor : public virtual BottomGraphAccessorInterface<1>
{
public:
    typename Graph<200, 1>::Container getBottomBuffers() const override
    {
        return {T{}.getBuffer()};
    }
};

template<std::size_t COUNT0, std::size_t COUNT1>
class SplitGraphDisplay :
    public Display,
    public virtual TitleInterface,
    public virtual TopGraphAccessorInterface<COUNT0>,
    public virtual BottomGraphAccessorInterface<COUNT1>,
    public virtual ConfirmInterface,
    public virtual BackInterface
{
    using Base = Display;

public:
    void initScreen(TftInterface &tft) override;
    void redraw(TftInterface &tft) override;

    void buttonPressed(Button button) override;

private:
    Label m_titleLabel{5, 5}; // 230, 25

    Graph<200, COUNT0> m_graph0{0, 40, 133};
    Graph<200, COUNT1> m_graph1{0, 179, 133};
};

template<std::size_t COUNT0, std::size_t COUNT1>
void SplitGraphDisplay<COUNT0, COUNT1>::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    m_titleLabel.start(tft);
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    m_graph0.start(tft, static_cast<const TopGraphAccessorInterface<COUNT0>&>(*this).getTopBuffers());
    m_graph1.start(tft, static_cast<const BottomGraphAccessorInterface<COUNT1>&>(*this).getBottomBuffers());
}

template<std::size_t COUNT0, std::size_t COUNT1>
void SplitGraphDisplay<COUNT0, COUNT1>::redraw(TftInterface &tft)
{
    m_titleLabel.redraw(tft, title(), TFT_YELLOW, TFT_BLACK, 4);

    m_graph0.redraw(tft, static_cast<const TopGraphAccessorInterface<COUNT0>&>(*this).getTopBuffers());
    m_graph1.redraw(tft, static_cast<const BottomGraphAccessorInterface<COUNT1>&>(*this).getBottomBuffers());
}

template<std::size_t COUNT0, std::size_t COUNT1>
void SplitGraphDisplay<COUNT0, COUNT1>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Left: back(); break;
    case Button::Right: confirm(); break;
    default:;
    }
}

} // namespace espgui
