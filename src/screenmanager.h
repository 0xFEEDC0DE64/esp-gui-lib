#pragma once

// system includes
#include <memory>
#include <functional>
#include <utility>
#include <stack>

// local includes
#include "display.h"

// forward declares
namespace espgui { class TftInterface; }

namespace espgui {

extern std::unique_ptr<Display> currentDisplay;

extern std::stack<std::unique_ptr<Display>> displayStack;

extern std::function<void(TftInterface&)> changeScreenCallback;

void deconstructScreen();

void pushScreenInternal();

void popScreenImpl(TftInterface &tft);
void popScreen();

template<typename T, typename... Args>
void switchScreen(Args... args)
{
    changeScreenCallback = [args...](TftInterface &tft){
        deconstructScreen();

        currentDisplay = std::make_unique<T>(args...);
        currentDisplay->start();
        currentDisplay->initScreen(tft);
        currentDisplay->update();
        currentDisplay->redraw(tft);
    };
}

template<typename T, typename... Args>
void switchScreenRef(Args&&... args)
{
    changeScreenCallback = [args...](TftInterface &tft){
        deconstructScreen();

        currentDisplay = std::make_unique<T>(std::forward<Args>(args)...);
        currentDisplay->start();
        currentDisplay->initScreen(tft);
        currentDisplay->update();
        currentDisplay->redraw(tft);
    };
}

template<typename T, typename... Args>
void pushScreen(Args... args)
{
    changeScreenCallback = [args...](TftInterface &tft){
        pushScreenInternal();

        currentDisplay = std::make_unique<T>(args...);
        currentDisplay->start();
        currentDisplay->initScreen(tft);
        currentDisplay->update();
        currentDisplay->redraw(tft);
    };
}

template<typename T, typename... Args>
void pushScreenRef(Args&&... args)
{
    changeScreenCallback = [args...](TftInterface &tft){
        pushScreenInternal();

        currentDisplay = std::make_unique<T>(std::forward<Args>(args)...);
        currentDisplay->start();
        currentDisplay->initScreen(tft);
        currentDisplay->update();
        currentDisplay->redraw(tft);
    };
}

} // namespace espgui
