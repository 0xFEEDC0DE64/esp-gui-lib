#include "changevaluedisplay_daylightsavingmode.h"

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

constexpr char TEXT_NONE[] = "None";
constexpr char TEXT_EUROPEANSUMMERTIME[] = "EuropeanSummerTime";
constexpr char TEXT_USDAYLIGHTTIME[] = "UsDaylightTime";
constexpr char TEXT_BACK[] = "Back";
} // namespace

ChangeValueDisplay<espchrono::DayLightSavingMode>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<espchrono::DayLightSavingMode>, StaticText<TEXT_NONE>>>(espchrono::DayLightSavingMode::None, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<espchrono::DayLightSavingMode>, StaticText<TEXT_EUROPEANSUMMERTIME>>>(espchrono::DayLightSavingMode::EuropeanSummerTime, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<espchrono::DayLightSavingMode>, StaticText<TEXT_USDAYLIGHTTIME>>>(espchrono::DayLightSavingMode::UsDaylightTime, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back, &icons::back_grey>>>(*this);
}

void ChangeValueDisplay<espchrono::DayLightSavingMode>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case espchrono::DayLightSavingMode::None:               setSelectedIndex(0); break;
    case espchrono::DayLightSavingMode::EuropeanSummerTime: setSelectedIndex(1); break;
    case espchrono::DayLightSavingMode::UsDaylightTime:     setSelectedIndex(2); break;
    default:
        ESP_LOGW(TAG, "Unknown DayLightSavingMode: %i", std::to_underlying(value));
        setSelectedIndex(3);
    }
}
}
