#pragma once

// local includes
#include "menuitem.h"
#include "accessorinterface.h"
#include "icons/checked.h"
#include "icons/checked_grey.h"
#include "icons/unchecked.h"
#include "icons/unchecked_grey.h"

namespace espgui {
class CheckboxIcon : public virtual MenuItemIconInterface, public virtual AccessorInterface<bool>
{
public:
    const MenuItemIcon *icon(bool selected) const override
    {
        return getValue() ? (selected ? &icons::checked_grey : &icons::checked) : (selected ? &icons::unchecked_grey : &icons::unchecked);
    }
};
} // namespace espgui
