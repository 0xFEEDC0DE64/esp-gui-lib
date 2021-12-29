#pragma once

// esp-idf includes
#include <esp_wifi_types.h>

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "actioninterface.h"

namespace espgui {

template<>
class ChangeValueDisplay<wifi_mode_t> :
    public MenuDisplay,
    public virtual AccessorInterface<wifi_mode_t>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
