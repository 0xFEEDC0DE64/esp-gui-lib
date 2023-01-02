#pragma once

//system includes
#include <cstdint>

namespace espgui {

enum Button
{
    Left,
    Right,
    Up,
    Down,
    ButtonMax = Down
};

inline std::string toString(Button button)
{
    switch (button)
    {
    case Button::Left: return "Left";
    case Button::Right: return "Right";
    case Button::Up: return "Up";
    case Button::Down: return "Down";
    default: return "Unknown";
    }
}

class ButtonsInterface
{
public:
    virtual void rawButtonPressed(uint8_t button) = 0;
    virtual void rawButtonReleased(uint8_t button) = 0;

    virtual void buttonPressed(Button button) = 0;
    virtual void buttonReleased(Button button) = 0;
};

} // namespace espgui
