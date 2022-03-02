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

template<typename Tscreen, typename ...Targs>
class SwitchScreenActionArgs;

template<typename Tscreen, typename T1>
class SwitchScreenActionArgs<Tscreen, T1> : public virtual ActionInterface
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

template<typename Tscreen, typename T1, typename T2>
class SwitchScreenActionArgs<Tscreen, T1, T2> : public virtual ActionInterface
{
public:
    SwitchScreenActionArgs(T1 &&arg1, T2 &&arg2) :
        m_arg1{std::move<T1>(arg1)},
        m_arg2{std::move<T2>(arg2)}
    {}
    SwitchScreenActionArgs(const T1 &arg1, const T2 &arg2) :
        m_arg1{arg1},
        m_arg2{arg2}
    {}

    void triggered() override { switchScreen<Tscreen>(std::move(m_arg1), std::move(m_arg2)); }

private:
    T1 m_arg1;
    T2 m_arg2;
};

} // namespace espgui
