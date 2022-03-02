#include "screenmanager.h"

namespace espgui {

std::unique_ptr<Display> currentDisplay;
std::stack<std::unique_ptr<Display>> displayStack;

std::function<void()> changeScreenCallback;

void deconstructScreen()
{
    if (currentDisplay)
    {
        currentDisplay->stop();
        currentDisplay = nullptr;
    }
}

void pushScreenInternal()
{
    if (currentDisplay)
    {
        currentDisplay->stop();
        displayStack.push(std::move(currentDisplay));
        assert(!currentDisplay);
    }
}

void popScreen()
{
    deconstructScreen();

    if (displayStack.empty())
        return;

    currentDisplay = std::move(displayStack.top());
    displayStack.pop();
    currentDisplay->start();
    currentDisplay->initScreen();
    currentDisplay->update();
    currentDisplay->redraw();
}

} // namespace espgui
