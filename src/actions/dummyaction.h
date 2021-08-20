#pragma once

// local includes
#include "actioninterface.h"

namespace espgui {
class DummyAction : public virtual ActionInterface
{
public:
    void triggered() override {}
};
} // namespace espgui
