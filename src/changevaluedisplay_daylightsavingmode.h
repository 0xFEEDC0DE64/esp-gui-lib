#pragma once

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "actioninterface.h"

namespace espgui {

template<>
class ChangeValueDisplay<espchrono::DayLightSavingMode> :
    public MenuDisplay,
    public virtual AccessorInterface<espchrono::DayLightSavingMode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
