#include "changevaluedisplay_bool.h"

// local includes
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"

namespace espgui {
namespace {
constexpr char TEXT_TRUE[] = "true";
constexpr char TEXT_FALSE[] = "false";
constexpr char TEXT_BACK[] = "Back";
} // namespace

ChangeValueDisplay<bool>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<bool>, StaticText<TEXT_TRUE>>>(true, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<bool>, StaticText<TEXT_FALSE>>>(false, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>>>(*this);
}

void ChangeValueDisplay<bool>::start()
{
    Base::start();

    switch (getValue())
    {
    case true:  setSelectedIndex(0); break;
    case false: setSelectedIndex(1); break;
    }
}
} // namespace espgui
