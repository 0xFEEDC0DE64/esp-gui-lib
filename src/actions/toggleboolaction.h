#pragma once

// local includes
#include "actioninterface.h"
#include "accessorinterface.h"
#include "errorhandlerinterface.h"

namespace espgui {
class ToggleBoolAction :
    public virtual ActionInterface,
    public virtual AccessorInterface<bool>,
    public virtual ErrorHandlerInterface
{
public:
    void triggered() override
    {
        if (auto result = setValue(!getValue()); !result)
            errorOccurred(std::move(result).error());
    }
};
} // namespace espgui
