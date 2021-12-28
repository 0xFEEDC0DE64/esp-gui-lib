#pragma once

// system includes
#include <string>
#include <cstdint>

// forward declares
namespace espgui {
class TextInterface;
class MenuDisplay;
class ChangeValueDisplayInterface;
}

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

enum Button
{
    Left,
    Right,
    Up,
    Down,
    ButtonMax = Down
};

class Display
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

    virtual void rawButtonPressed(uint8_t button) = 0;
    virtual void rawButtonReleased(uint8_t button) = 0;

    virtual void buttonPressed(Button button) = 0;
    virtual void buttonReleased(Button button) = 0;

    virtual TextInterface *asTextInterface() { return nullptr; }
    virtual const TextInterface *asTextInterface() const { return nullptr; }

    virtual MenuDisplay *asMenuDisplay() { return nullptr; }
    virtual const MenuDisplay *asMenuDisplay() const { return nullptr; }

    virtual ChangeValueDisplayInterface *asChangeValueDisplayInterface() { return nullptr; }
    virtual const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const { return nullptr; }
};
} // namespace espgui
