#include "screenmanager.h"

namespace espgui {

std::unique_ptr<Display> currentDisplay;
std::function<void()> changeScreenCallback;

void deconstructScreen()
{
    if (currentDisplay)
    {
        currentDisplay->stop();
        currentDisplay = nullptr;
    }
}

} // namespace espgui
