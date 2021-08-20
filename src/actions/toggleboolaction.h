#pragma once

// local includes
#include "actioninterface.h"
#include "accessorinterface.h"

namespace espgui {
class ToggleBoolAction :
    public virtual ActionInterface,
    public virtual AccessorInterface<bool>
{
public:
    void triggered() override
    {
        setValue(!getValue());
    }
};
} // namespace espgui
