#pragma once

// local includes
#include "popupdisplay.h"

namespace espgui {

class MessagePopupDisplay : public PopupDisplay
{
    using Base = PopupDisplay;

public:
    MessagePopupDisplay(std::string &&message, std::unique_ptr<Display> &&lastDisplay);

    void buttonPressed(Button button) override;

    void initOverlay(TftInterface &tft) override;

private:
    std::string m_message;
};

} // namespace espgui
