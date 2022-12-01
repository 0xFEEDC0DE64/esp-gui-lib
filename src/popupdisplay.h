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

    void initScreen(TftInterface &tft) override;

    void redraw(TftInterface &tft) override;

    virtual void initOverlay(TftInterface &tft) = 0;
    void closeOverlay();
    void closeOverlay(TftInterface &tft);

private:
    std::unique_ptr<Display> m_lastDisplay;

    bool m_wantsClose{};
};

} // namespace espgui
