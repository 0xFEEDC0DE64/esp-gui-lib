#include "changevaluedisplay_sntp_sync_mode_t.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "icons/back_grey.h"

namespace espgui {
namespace {
constexpr const char * const TAG = "ESPGUI";

constexpr char TEXT_IMMED[] = "IMMED";
constexpr char TEXT_SMOOTH[] = "SMOOTH";
constexpr char TEXT_BACK[] = "Back";
} // namespace

ChangeValueDisplay<sntp_sync_mode_t>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<sntp_sync_mode_t>, StaticText<TEXT_IMMED>>>(SNTP_SYNC_MODE_IMMED, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<sntp_sync_mode_t>, StaticText<TEXT_SMOOTH>>>(SNTP_SYNC_MODE_SMOOTH, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back, &icons::back_grey>>>(*this);
}

void ChangeValueDisplay<sntp_sync_mode_t>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case SNTP_SYNC_MODE_IMMED:  setSelectedIndex(0); break;
    case SNTP_SYNC_MODE_SMOOTH: setSelectedIndex(1); break;
    default:
        ESP_LOGW(TAG, "Unknown sntp_sync_mode_t: %i", std::to_underlying(value));
        setSelectedIndex(2);
    }
}
}
