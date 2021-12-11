#pragma once

// local includes
#include "actioninterface.h"
#include "display.h"

namespace espgui {
class BackProxyAction : public virtual ActionInterface
{
public:
    BackProxyAction(BackInterface &backInterface) :
        m_backInterface{backInterface}
    {
    }

    void triggered() override
    {
        m_backInterface.back();
    }

private:
    BackInterface &m_backInterface;
};
} // namespace espgui
