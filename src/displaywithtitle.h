#pragma once

// local includes
#include "display.h"
#include "titleinterface.h"
#include "widgets/label.h"

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
    Label m_titleLabel{5, 5}; // 230, 25
};

} // namespace espgui
