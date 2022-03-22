#pragma once

// local includes
#include "actioninterface.h"
#include "menuitem.h"
#include "textinterface.h"
#include "scrollinterface.h"

namespace espgui {
class MarginMenuItem :
        public virtual MenuItem,
        public EmptyText,
        public virtual ActionInterface,
        public virtual ScrollInterface
{
public:
    void triggered() override {}
    bool skipScroll() const override { return true; }
};
} // namespace espgui
