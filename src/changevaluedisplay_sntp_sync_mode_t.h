#pragma once

// esp-idf includes
#include <esp_sntp.h>

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"

namespace espgui {
template<>
class ChangeValueDisplay<sntp_sync_mode_t> :
    public MenuDisplay,
    public virtual AccessorInterface<sntp_sync_mode_t>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};
} // namespace espgui
