#pragma once

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "actioninterface.h"

namespace espgui {
template<>
class ChangeValueDisplay<bool> :
    public MenuDisplay,
    public virtual AccessorInterface<bool>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};
} // namespace espgui
