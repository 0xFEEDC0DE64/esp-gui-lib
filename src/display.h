#pragma once

// system includes
#include <string>
#include <cstdint>

// local includes
#include "buttonsinterface.h"

// forward declares
namespace espgui {
class TextInterface;
class MenuDisplay;
class ChangeValueDisplayInterface;
template<typename Tvalue> class ChangeValueDisplay;
} // namespace espgui
namespace wifi_stack {
class ip_address_t;
} // namespace wifi_stack

namespace espgui {

template<typename ...T>
class makeComponent : public T...
{};

template <typename T1, typename T2, typename ...T3>
class makeComponentArgs : public T1, public T2, public T3...
{
public:
    template<typename ...T>
    makeComponentArgs(T&& ...args) :
        T2{std::forward<T>(args)...}
    {
    }
};

template <typename T1, typename T2, typename T3, typename ...T4>
class makeComponentArgs2 : public T1, public T2, public T3, public T4...
{
public:
    template<typename Targ1, typename Targ2>
    makeComponentArgs2(Targ1&& arg1, Targ2&& arg2) :
        T2{std::forward<Targ1>(arg1)},
        T3{std::forward<Targ2>(arg2)}
    {
    }
};

class Display : public virtual ButtonsInterface
{
public:
    virtual ~Display() = default;

    //! Display comes into existance, is shown
    virtual void start() {}

    //! Display needs to fully initialize screen
    virtual void initScreen();

    //! Display can do work needed to update correctly
    virtual void update() {}

    //! Display can update screen incrementally
    virtual void redraw() {}

    //! Display goes out of existance, is not shown anymore
    virtual void stop() {}

    virtual TextInterface *asTextInterface() { return nullptr; }
    virtual const TextInterface *asTextInterface() const { return nullptr; }

    virtual MenuDisplay *asMenuDisplay() { return nullptr; }
    virtual const MenuDisplay *asMenuDisplay() const { return nullptr; }

    virtual ChangeValueDisplayInterface *asChangeValueDisplayInterface() { return nullptr; }
    virtual const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const { return nullptr; }

    virtual ChangeValueDisplay<std::string> *asChangeValueDisplayString() { return nullptr; }
    virtual const ChangeValueDisplay<std::string> *asChangeValueDisplayString() const { return nullptr; }

    virtual ChangeValueDisplay<wifi_stack::ip_address_t> *asChangeValueDisplayIpAddress() { return nullptr; }
    virtual const ChangeValueDisplay<wifi_stack::ip_address_t> *asChangeValueDisplayIpAddress() const { return nullptr; }
};

} // namespace espgui
