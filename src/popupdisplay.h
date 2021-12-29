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
    PopupDisplay(std::string &&message, std::unique_ptr<Display> &&lastDisplay);

    //void start() override;
    void initScreen() override;
    //void update() override;
    //void redraw() override;
    //void stop() override;

    void buttonPressed(espgui::Button button) override;

    virtual void initOverlay();
    virtual void closeOverlay();

private:
    std::string m_message;
    std::unique_ptr<Display> m_lastDisplay;
};

} // namespace espgui
