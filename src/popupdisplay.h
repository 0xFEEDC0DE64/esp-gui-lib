#pragma once

// system includes
#include <memory>

// local includes
#include "display.h"

namespace espgui {

class PopupDisplay : public Display
{
    using Base = Display;

public:
    PopupDisplay(std::unique_ptr<Display> &&lastDisplay);

    void initScreen() override;

    virtual void initOverlay() = 0;
    void closeOverlay();

private:
    std::unique_ptr<Display> m_lastDisplay;
};

} // namespace espgui
