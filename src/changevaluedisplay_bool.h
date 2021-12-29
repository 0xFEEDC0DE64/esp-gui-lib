#pragma once

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "confirminterface.h"
#include "errorhandlerinterface.h"

namespace espgui {

template<>
class ChangeValueDisplay<bool> :
    public MenuDisplay,
    public virtual AccessorInterface<bool>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
