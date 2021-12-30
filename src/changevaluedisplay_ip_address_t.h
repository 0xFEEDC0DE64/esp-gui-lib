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

public:
    ChangeValueDisplay<wifi_stack::ip_address_t> *asChangeValueDisplayIpAddress() override { return this; }
    const ChangeValueDisplay<wifi_stack::ip_address_t> *asChangeValueDisplayIpAddress() const override { return this; }

    void start() override;
    void initScreen() override;
    void update() override;
    void redraw() override;

    void buttonPressed(Button button) override;

    wifi_stack::ip_address_t shownValue() const { return m_value; }
    void setShownValue(wifi_stack::ip_address_t value) { m_value = value; }

private:
    wifi_stack::ip_address_t m_value;
    bool m_pressed{};

    Label m_valueLabel{26, 81}; // 188, 53
};

} // namespace espgui
