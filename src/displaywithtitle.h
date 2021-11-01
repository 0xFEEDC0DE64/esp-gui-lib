#pragma once

// local includes
#include "display.h"
#include "textinterface.h"
#include "widgets/label.h"

namespace espgui {

class DisplayWithTitle :
    public Display,
    public virtual TextInterface
{
    using Base = Display;

public:
    TextInterface *asTextInterface() override { return this; }
    const TextInterface *asTextInterface() const override { return this; }

    void initScreen() override;
    void redraw() override;

private:
    Label m_titleLabel{5, 5}; // 230, 25
};

} // namespace espgui
