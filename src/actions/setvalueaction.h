#pragma once

// local includes
#include "display.h"
#include "actioninterface.h"
#include "accessorinterface.h"

namespace espgui {
template<typename T>
class SetValueAction : public virtual ActionInterface
{
public:
    SetValueAction(T value, AccessorInterface<T> &accessorInterface, BackInterface &backInterface) :
        m_value{value},
        m_accessorInterface{accessorInterface},
        m_backInterface{backInterface}
    {
    }

    void triggered() override
    {
        // TODO: implement error handling and show popup in case of error
        m_accessorInterface.setValue(m_value);

        m_backInterface.back();
    }

    T value() const { return m_value; }

private:
    const T m_value;
    AccessorInterface<T> &m_accessorInterface;
    BackInterface &m_backInterface;
};
} // namespace espgui
