#include "changevaluedisplay_wifi_auth_mode_t.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"

namespace espgui {
namespace {
constexpr const char * const TAG = "ESPGUI";

constexpr char TEXT_OPEN[] = "OPEN";
constexpr char TEXT_WEP[] = "WEP";
constexpr char TEXT_WPA_PSK[] = "WPA_PSK";
constexpr char TEXT_WPA2_PSK[] = "WPA2_PSK";
constexpr char TEXT_WPA_WPA2_PSK[] = "WPA_WPA2_PSK";
constexpr char TEXT_WPA2_ENTERPRISE[] = "WPA2_ENTERPRISE";
constexpr char TEXT_WPA3_PSK[] = "WPA3_PSK";
constexpr char TEXT_WPA2_WPA3_PSK[] = "WPA2_WPA3_PSK";
constexpr char TEXT_WAPI_PSK[] = "WAPI_PSK";
constexpr char TEXT_BACK[] = "BACK";
} // namespace

ChangeValueDisplay<wifi_auth_mode_t>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_OPEN>>>(WIFI_AUTH_OPEN, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WEP>>>(WIFI_AUTH_WEP, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WPA_PSK>>>(WIFI_AUTH_WPA_PSK, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WPA2_PSK>>>(WIFI_AUTH_WPA2_PSK, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WPA_WPA2_PSK>>>(WIFI_AUTH_WPA_WPA2_PSK, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WPA2_ENTERPRISE>>>(WIFI_AUTH_WPA2_ENTERPRISE, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WPA3_PSK>>>(WIFI_AUTH_WPA3_PSK, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WPA2_WPA3_PSK>>>(WIFI_AUTH_WPA2_WPA3_PSK, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<wifi_auth_mode_t>, StaticText<TEXT_WAPI_PSK>>>(WIFI_AUTH_WAPI_PSK, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&espgui::icons::back>>>(*this);
}

void ChangeValueDisplay<wifi_auth_mode_t>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case WIFI_AUTH_OPEN:            setSelectedIndex(0); break;
    case WIFI_AUTH_WEP:             setSelectedIndex(1); break;
    case WIFI_AUTH_WPA_PSK:         setSelectedIndex(2); break;
    case WIFI_AUTH_WPA2_PSK:        setSelectedIndex(3); break;
    case WIFI_AUTH_WPA_WPA2_PSK:    setSelectedIndex(4); break;
    case WIFI_AUTH_WPA2_ENTERPRISE: setSelectedIndex(5); break;
    case WIFI_AUTH_WPA3_PSK:        setSelectedIndex(6); break;
    case WIFI_AUTH_WPA2_WPA3_PSK:   setSelectedIndex(7); break;
    case WIFI_AUTH_WAPI_PSK:        setSelectedIndex(8); break;
    default:
        ESP_LOGW(TAG, "Unknown wifi_auth_mode_t: %i", std::to_underlying(value));
        setSelectedIndex(9);
    }
}

} // namespace espgui
