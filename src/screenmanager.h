#pragma once

// system includes
#include <memory>
#include <functional>
#include <utility>
#include <stack>

// local includes
#include "display.h"

namespace espgui {

extern std::unique_ptr<Display> currentDisplay;

extern std::stack<std::unique_ptr<Display>> displayStack;

extern std::function<void()> changeScreenCallback;

void deconstructScreen();

void pushScreenInternal();

void popScreen();

template<typename T, typename... Args>
void switchScreenImpl(Args... args)
{
    deconstructScreen();

    currentDisplay = std::make_unique<T>(args...);
    currentDisplay->start();
    currentDisplay->initScreen();
    currentDisplay->update();
    currentDisplay->redraw();
}

template<typename T, typename... Args>
void switchScreenRefImpl(Args&&... args)
{
    deconstructScreen();

    currentDisplay = std::make_unique<T>(std::forward<Args>(args)...);
    currentDisplay->start();
    currentDisplay->initScreen();
    currentDisplay->update();
    currentDisplay->redraw();
}

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

template<typename T, typename... Args>
void pushScreenImpl(Args... args)
{
    pushScreenInternal();

    currentDisplay = std::make_unique<T>(args...);
    currentDisplay->start();
    currentDisplay->initScreen();
    currentDisplay->update();
    currentDisplay->redraw();
}

template<typename T, typename... Args>
void pushScreenRefImpl(Args&&... args)
{
    pushScreenInternal();

    currentDisplay = std::make_unique<T>(std::forward<Args>(args)...);
    currentDisplay->start();
    currentDisplay->initScreen();
    currentDisplay->update();
    currentDisplay->redraw();
}

template<typename T, typename... Args>
void pushScreen(Args... args)
{
    if (currentDisplay)
        changeScreenCallback = [args...](){ pushScreenImpl<T>(args...); };
    else
        pushScreenImpl<T>(args...);
}

template<typename T, typename... Args>
void pushScreenRef(Args&&... args)
{
    if (currentDisplay)
        changeScreenCallback = [args...](){ pushScreenRefImpl<T>(std::forward<Args>(args)...); };
    else
        pushScreenRefImpl<T>(std::forward<Args>(args)...);
}

} // namespace espgui
