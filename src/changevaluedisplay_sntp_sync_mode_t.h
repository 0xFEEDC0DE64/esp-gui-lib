#pragma once

// esp-idf includes
#include <esp_sntp.h>

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "confirminterface.h"
#include "errorhandlerinterface.h"

namespace espgui {

template<>
class ChangeValueDisplay<sntp_sync_mode_t> :
    public MenuDisplay,
    public virtual AccessorInterface<sntp_sync_mode_t>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
