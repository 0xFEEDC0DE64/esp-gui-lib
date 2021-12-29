#pragma once

// local includes
#include "actioninterface.h"
#include "accessorinterface.h"
#include "confirminterface.h"
#include "errorhandlerinterface.h"

namespace espgui {
template<typename T>
class SetValueAction : public virtual ActionInterface
{
public:
    SetValueAction(T value,AccessorInterface<T> &accessorInterface,
                   ConfirmInterface &confirmInterface, ErrorHandlerInterface &errorHandlerInterface) :
        m_value{value},
        m_accessorInterface{accessorInterface},
        m_confirmInterface{confirmInterface},
        m_errorHandlerInterface{errorHandlerInterface}
    {
    }

    void triggered() override
    {
        if (auto result = m_accessorInterface.setValue(m_value); result)
            m_confirmInterface.confirm();
        else
            m_errorHandlerInterface.errorOccured(std::move(result).error());
    }

    T value() const { return m_value; }

private:
    const T m_value;
    AccessorInterface<T> &m_accessorInterface;
    ConfirmInterface &m_confirmInterface;
    ErrorHandlerInterface &m_errorHandlerInterface;
};
} // namespace espgui
