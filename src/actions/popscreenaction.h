#pragma once

// system includes
#include <utility>

// local includes
#include "actioninterface.h"
#include "screenmanager.h"

namespace espgui {

class PopScreenAction : public virtual ActionInterface
{
public:
    void triggered() override { popScreen(); }
};

} // namespace espgui
