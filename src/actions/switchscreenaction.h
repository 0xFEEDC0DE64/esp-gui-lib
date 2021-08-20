#pragma once

// local includes
#include "actioninterface.h"
#include "screenmanager.h"

namespace espgui {
template<typename Tscreen, typename ...Targs>
class SwitchScreenAction : public virtual ActionInterface
{
public:
    void triggered() override { switchScreen<Tscreen>(std::make_unique<Targs>()...); }
};
} // namespace espgui
