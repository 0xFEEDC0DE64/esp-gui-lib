#pragma once

// 3rdparty lib includes
#include <espwifiutils.h>

// local includes
#include "changevaluedisplay.h"
#include "displaywithtitle.h"
#include "confirminterface.h"
#include "backinterface.h"
#include "errorhandlerinterface.h"
#include "widgets/label.h"

namespace espgui {

template<>
class ChangeValueDisplay<wifi_stack::ip_address_t> :
    public DisplayWithTitle,
    public virtual AccessorInterface<wifi_stack::ip_address_t>,
    public virtual ConfirmInterface,
    public virtual BackInterface,
    public virtual ErrorHandlerInterface
{
    using Base = DisplayWithTitle;

    static constexpr auto boxWidth = 50;
    static constexpr auto boxHeight = 25;
    static constexpr auto spacing = 20;

    static constexpr auto y = 90;

public:
    ChangeValueDisplay<wifi_stack::ip_address_t> *asChangeValueDisplayIpAddress() override { return this; }
    const ChangeValueDisplay<wifi_stack::ip_address_t> *asChangeValueDisplayIpAddress() const override { return this; }

    void start() override;
    void initScreen(TftInterface &tft) override;
    void update() override;
    void redraw(TftInterface &tft) override;

    void buttonPressed(Button button) override;
    void buttonReleased(Button button) override;

    wifi_stack::ip_address_t shownValue() const { return m_value; }
    void setShownValue(wifi_stack::ip_address_t value) { m_value = value; }

private:
    void drawRect(TftInterface &tft, int index, int offset, uint32_t color) const;

    wifi_stack::ip_address_t m_value;

    std::array<espgui::Label, 4> m_labels {{
        espgui::Label{spacing, y},              // boxWidth, boxHeight
        espgui::Label{spacing*2+boxWidth, y},   // boxWidth, boxHeight
        espgui::Label{spacing*3+boxWidth*2, y}, // boxWidth, boxHeight
        espgui::Label{spacing*4+boxWidth*3, y}  // boxWidth, boxHeight
    }};

    uint8_t m_currentIndex{};
    uint8_t m_lastIndex{};
};

} // namespace espgui
