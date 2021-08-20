#include "screenmanager.h"

namespace espgui {

std::unique_ptr<Display> currentDisplay;
std::function<void()> changeScreenCallback;

} // namespace espgui
