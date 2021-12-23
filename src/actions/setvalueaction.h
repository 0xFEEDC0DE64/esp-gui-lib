#pragma once

// local includes
#include "actioninterface.h"
#include "accessorinterface.h"

namespace espgui {
template<typename T>
class SetValueAction : public virtual ActionInterface
{
public:
    SetValueAction(T value, AccessorInterface<T> &accessorInterface, ActionInterface &actionInterface) :
        m_value{value},
        m_accessorInterface{accessorInterface},
        m_actionInterface{actionInterface}
    {
    }

    void triggered() override
    {
        // TODO: implement error handling and show popup in case of error
        m_accessorInterface.setValue(m_value);

        m_actionInterface.triggered();
    }

    T value() const { return m_value; }

private:
    const T m_value;
    AccessorInterface<T> &m_accessorInterface;
    ActionInterface &m_actionInterface;
};
} // namespace espgui
