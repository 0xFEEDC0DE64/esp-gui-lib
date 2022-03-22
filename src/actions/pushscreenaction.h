#pragma once

// system includes
#include <utility>
#include <type_traits>

// local includes
#include "actioninterface.h"
#include "screenmanager.h"

namespace espgui {

template<typename Tscreen>
class PushScreenAction : public virtual ActionInterface
{
public:
    void triggered() override { pushScreen<Tscreen>(); }
};

template<typename Tscreen, typename ...Targs>
class PushScreenActionArgs;

template<typename Tscreen, typename T1>
class PushScreenActionArgs<Tscreen, T1> : public virtual ActionInterface
{
public:
    template<typename U = T1> // to get SFINAE
    PushScreenActionArgs(typename std::enable_if_t<!std::is_integral_v<U>, U> &&arg1) :
        m_arg1{std::move<T1>(arg1)}
    {}
    PushScreenActionArgs(const T1 &arg1) :
        m_arg1{arg1}
    {}

    void triggered() override { pushScreen<Tscreen>(std::move(m_arg1)); }

private:
    T1 m_arg1;
};

template<typename Tscreen, typename T1, typename T2>
class PushScreenActionArgs<Tscreen, T1, T2> : public virtual ActionInterface
{
public:
    PushScreenActionArgs(T1 &&arg1, T2 &&arg2) :
        m_arg1{std::move<T1>(arg1)},
        m_arg2{std::move<T2>(arg2)}
    {}
    PushScreenActionArgs(const T1 &arg1, const T2 &arg2) :
        m_arg1{arg1},
        m_arg2{arg2}
    {}

    void triggered() override { pushScreen<Tscreen>(std::move(m_arg1), std::move(m_arg2)); }

private:
    T1 m_arg1;
    T2 m_arg2;
};

} // namespace espgui
