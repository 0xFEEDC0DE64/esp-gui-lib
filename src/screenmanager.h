#pragma once

// system includes
#include <memory>
#include <functional>
#include <utility>

// local includes
#include "display.h"

namespace espgui {

extern std::unique_ptr<Display> currentDisplay;

inline void deconstructScreen()
{
    if (currentDisplay)
    {
        currentDisplay->stop();
        //currentDisplay->~Display();
        currentDisplay = nullptr;
    }
}

template<typename T, typename... Args>
void switchScreenImpl(Args... args)
{
    deconstructScreen();

    std::unique_ptr<T> ptr = std::make_unique<T>(args...);
    currentDisplay = std::move(ptr);
    currentDisplay->start();
    currentDisplay->initScreen();
    currentDisplay->update();
    currentDisplay->redraw();
}

template<typename T, typename... Args>
void switchScreenRefImpl(Args&&... args)
{
    deconstructScreen();

    std::unique_ptr<T> ptr = std::make_unique<T>(std::forward<Args>(args)...);
    currentDisplay = std::move(ptr);
    currentDisplay->start();
    currentDisplay->initScreen();
    currentDisplay->update();
    currentDisplay->redraw();
}

extern std::function<void()> changeScreenCallback;

template<typename T, typename... Args>
void switchScreen(Args... args)
{
    if (currentDisplay)
        changeScreenCallback = [args...](){ switchScreenImpl<T>(args...); };
    else
        switchScreenImpl<T>(args...);
}

template<typename T, typename... Args>
void switchScreenRef(Args&&... args)
{
    if (currentDisplay)
        changeScreenCallback = [args...](){ switchScreenRefImpl<T>(std::forward<Args>(args)...); };
    else
        switchScreenRefImpl<T>(std::forward<Args>(args)...);
}

} // namespace espgui
