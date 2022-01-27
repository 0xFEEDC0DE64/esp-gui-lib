#pragma once

// system includes
#include <utility>

// local includes
#include "actioninterface.h"
#include "screenmanager.h"

namespace espgui {
template<typename Tscreen>
class SwitchScreenAction : public virtual ActionInterface
{
public:
    void triggered() override { switchScreen<Tscreen>(); }
};

template<typename Tscreen, typename T1>
class SwitchScreenActionArgs : public virtual ActionInterface
{
public:
    SwitchScreenActionArgs(T1 &&arg1) :
        m_arg1{std::move<T1>(arg1)}
    {}
    SwitchScreenActionArgs(const T1 &arg1) :
        m_arg1{arg1}
    {}

    void triggered() override { switchScreen<Tscreen>(std::move(m_arg1)); }

private:
    T1 m_arg1;
};
} // namespace espgui
