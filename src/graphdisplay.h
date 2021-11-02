#pragma once

// 3rdparty lib includes
#include <ring-buffer.h>

// local includes
#include "displaywithtitle.h"
#include "textinterface.h"
#include "widgets/label.h"
#include "widgets/graph.h"
#include "tftinstance.h"

namespace espgui {
template<size_t COUNT>
class GraphAccessorInterface
{
public:
    virtual std::array<std::reference_wrapper<const ring_buffer<float, 200>>, COUNT> getBuffers() const = 0;
};

template<typename T>
class SingleGraphAccessor : public virtual GraphAccessorInterface<1>
{
public:
    Graph<200, 1>::Container getBuffers() const
    {
        return {T{}.getBuffer()};
    }
};

template<typename T1, typename T2>
class DualGraphAccessor : public virtual GraphAccessorInterface<2>
{
public:
    Graph<200, 2>::Container getBuffers() const
    {
        return {T1{}.getBuffer(), T2{}.getBuffer()};
    }
};

template<size_t COUNT>
class GraphDisplay :
    public DisplayWithTitle,
    public virtual GraphAccessorInterface<COUNT>
{
    using Base = DisplayWithTitle;

public:
    void initScreen() override;
    void redraw() override;

private:
    static constexpr int screenHeight = 320, topMargin = 40, bottomMargin = 10, labelOffset = -5;
    static constexpr int graphHeight = screenHeight-topMargin-bottomMargin;

    Graph<200, COUNT> m_graph{0, 40, 270};
};

template<size_t COUNT>
void GraphDisplay<COUNT>::initScreen()
{
    Base::initScreen();

    m_graph.start(static_cast<const GraphAccessorInterface<COUNT> &>(*this).getBuffers());
}

template<size_t COUNT>
void GraphDisplay<COUNT>::redraw()
{
    m_graph.redraw(static_cast<const GraphAccessorInterface<COUNT> &>(*this).getBuffers());
}
}
