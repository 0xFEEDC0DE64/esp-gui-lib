#include "screenmanager.h"

// system includes
#include <cassert>

// esp-idf includes
#include <esp_log.h>

namespace espgui {

namespace {
constexpr const char * const TAG = "SCREENMANAGER";
} // namespace

std::unique_ptr<Display> currentDisplay;
std::stack<std::unique_ptr<Display>> displayStack;

std::function<void(TftInterface&)> changeScreenCallback;

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

void popScreenImpl(TftInterface &tft)
{
    deconstructScreen();

    if (displayStack.empty())
    {
        ESP_LOGW(TAG, "displayStack is empty");
        return;
    }

    currentDisplay = std::move(displayStack.top());
    displayStack.pop();
    currentDisplay->start();
    currentDisplay->initScreen(tft);
    currentDisplay->update();
    currentDisplay->redraw(tft);
}

void popScreen()
{
    changeScreenCallback = [](TftInterface &tft){ popScreenImpl(tft); };
}

} // namespace espgui
