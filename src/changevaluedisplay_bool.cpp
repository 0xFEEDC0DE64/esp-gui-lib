#include "changevaluedisplay_bool.h"

// local includes
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "icons/back_grey.h"

namespace espgui {
namespace {
constexpr char TEXT_TRUE[] = "true";
constexpr char TEXT_FALSE[] = "false";
constexpr char TEXT_BACK[] = "Back";
} // namespace

ChangeValueDisplay<bool>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<bool>, StaticText<TEXT_TRUE>>>(true, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<bool>, StaticText<TEXT_FALSE>>>(false, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back, &icons::back_grey>>>(*this);
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
