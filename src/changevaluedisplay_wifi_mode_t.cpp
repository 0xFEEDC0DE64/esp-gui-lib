#include "changevaluedisplay_wifi_mode_t.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"

namespace espgui {
namespace {
constexpr const char * const TAG = "ESPGUI";

constexpr char TEXT_NULL[] = "NULL";
constexpr char TEXT_STA[] = "STA";
constexpr char TEXT_AP[] = "AP";
constexpr char TEXT_APSTA[] = "APSTA";
constexpr char TEXT_BACK[] = "BACK";
} // namespace

ChangeValueDisplay<wifi_mode_t>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_NULL>>>(WIFI_MODE_NULL, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_STA>>>(WIFI_MODE_STA, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_AP>>>(WIFI_MODE_AP, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_APSTA>>>(WIFI_MODE_APSTA, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&espgui::icons::back>>>(*this);
}

void ChangeValueDisplay<wifi_mode_t>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case WIFI_MODE_NULL:  setSelectedIndex(0); break;
    case WIFI_MODE_STA:   setSelectedIndex(1); break;
    case WIFI_MODE_AP:    setSelectedIndex(2); break;
    case WIFI_MODE_APSTA: setSelectedIndex(3); break;
    default:
        ESP_LOGW(TAG, "Unknown wifi_mode_t: %i", std::to_underlying(value));
        setSelectedIndex(4);
    }
}

} // namespace espgui
