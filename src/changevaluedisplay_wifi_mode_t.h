#pragma once

// esp-idf includes
#include <esp_wifi_types.h>

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "confirminterface.h"
#include "errorhandlerinterface.h"

namespace espgui {

template<>
class ChangeValueDisplay<wifi_mode_t> :
    public MenuDisplay,
    public virtual AccessorInterface<wifi_mode_t>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
