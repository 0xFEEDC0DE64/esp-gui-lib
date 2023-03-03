#pragma once

// 3rdparty lib includes
#include <delayedconstruction.h>

// local includes
#include "display.h"
#include "titleinterface.h"
#include "widgets/scrolllabel.h"

namespace espgui {

class DisplayWithTitle :
    public Display,
    public virtual TitleInterface
{
    using Base = Display;

public:
    TitleInterface *asTitleInterface() override { return this; }
    const TitleInterface *asTitleInterface() const override { return this; }

    void initScreen(TftInterface &tft) override;
    void redraw(TftInterface &tft) override;

private:
    static constexpr const auto SCROLLMARGIN = 40;

    cpputils::DelayedConstruction<ScrollLabel> m_titleLabel;
};

} // namespace espgui
