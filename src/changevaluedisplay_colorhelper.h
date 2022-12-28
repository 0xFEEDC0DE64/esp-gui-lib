#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <color_utils.h>

// local includes
#include "backinterface.h"
#include "changevaluedisplay.h"
#include "confirminterface.h"
#include "displaywithtitle.h"
#include "errorhandlerinterface.h"

namespace espgui {

template<>
class ChangeValueDisplay<cpputils::ColorHelper> :
        public DisplayWithTitle,
        public virtual AccessorInterface<cpputils::ColorHelper>,
        public virtual ConfirmInterface,
        public virtual BackInterface,
        public virtual ErrorHandlerInterface
{
    using Base = DisplayWithTitle;

public:
    void start() override;
    void initScreen(TftInterface &tft) override;
    void redraw(TftInterface &tft) override;

    void buttonPressed(Button button) override;
    void buttonReleased(Button button) override;

    void drawHSVWheel(TftInterface &tft, int16_t x, int16_t y, uint8_t d) const;
    void confirmValue();
private:
    cpputils::ColorHelper m_value;
};

} // namespace espgui
