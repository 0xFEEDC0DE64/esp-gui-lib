#pragma once

// local includes
#include "textinterface.h"
#include "fontinterface.h"
#include "colorinterface.h"
#include "iconinterface.h"
#include "actioninterface.h"
#include "visibleinterface.h"
#include "scrollinterface.h"

namespace espgui {

using MenuItemIcon = Icon<24, 24>;

template<uint16_t width, uint16_t height>
class SelectableIconInterface
{
public:
    virtual const Icon<width, height> *icon(bool selected) const { return nullptr; }
};

template<uint16_t width, uint16_t height, const Icon<width, height> *T, const Icon<width, height> *Tselected>
class StaticSelectableIcon : public virtual SelectableIconInterface<width, height>
{
public:
    virtual const Icon<width, height> *icon(bool selected) const override { return selected ? Tselected : T; }
};

template<uint16_t width, uint16_t height>
class SelectedIconInterface
{
public:
    virtual const Icon<width, height> *selectedIcon() const { return nullptr; }
};

template<uint16_t width, uint16_t height, const Icon<width, height> *T>
class StaticSelectedIcon : public virtual SelectedIconInterface<width, height>
{
public:
    virtual const Icon<width, height> *selectedIcon() const override { return T; }
};

template<uint16_t width, uint16_t height>
class ChangeableSelectableIcon : public virtual SelectableIconInterface<width, height>
{
public:
    virtual const Icon<width, height> *icon(bool selected) const override { return selected ? m_selectedIcon : m_icon; }

    void setIcon(const Icon<width, height> *icon, const Icon<width, height> *selectedIcon)
    {
        m_icon = icon;
        m_selectedIcon = selectedIcon;
    }

    void setIcon(const Icon<width, height> *icon) { m_icon = icon; }
    void setSelectedIcon(const Icon<width, height> *selectedIcon) { m_selectedIcon = selectedIcon; }

private:
    const Icon<width, height> *m_icon = nullptr;
    const Icon<width, height> *m_selectedIcon = nullptr;
};

template<uint16_t width, uint16_t height>
class ChangeableSelectedIcon : public virtual SelectedIconInterface<width, height>
{
public:
    virtual const Icon<width, height> *selectedIcon() const override { return m_selectedIcon; }

    void setSelectedIcon(const Icon<width, height> *selectedIcon) { m_selectedIcon = selectedIcon; }

private:
    const Icon<width, height> *m_selectedIcon = nullptr;
};

using MenuItemIconInterface = SelectableIconInterface<24, 24>;

using MenuItemSelectedIconInterface = SelectedIconInterface<24, 24>;

template<const MenuItemIcon * ...T>
class StaticMenuItemIcon;

template<const MenuItemIcon *T, const MenuItemIcon *Tselected>
class StaticMenuItemIcon<T, Tselected> : public StaticSelectableIcon<24, 24, T, Tselected>
{
    using Base = StaticSelectableIcon<24, 24, T, Tselected>;

public:
    using Base::Base;
};

template<const MenuItemIcon *T>
class StaticMenuItemIcon<T> : public StaticSelectableIcon<24, 24, T, T>
{
    using Base = StaticSelectableIcon<24, 24, T, T>;

public:
    using Base::Base;
};

template<const MenuItemIcon *T>
using StaticMenuItemSelectedIcon = StaticSelectedIcon<24, 24, T>;

using ChangeableMenuItemIcon = ChangeableSelectableIcon<24, 24>;

using ChangeableMenuItemSelectedIcon = ChangeableSelectedIcon<24, 24>;

class MenuItem :
    public virtual ActionInterface,
    public virtual TextInterface,
    public virtual FontInterface,
    public virtual ColorInterface,
    public virtual MenuItemIconInterface,
    public virtual MenuItemSelectedIconInterface,
    public virtual VisibleInterface,
    public virtual ScrollInterface
{
public:
    virtual ~MenuItem() = default;
    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}
};

template<typename T>
class MenuItemWithMenuRef : public MenuItem
{
public:
    MenuItemWithMenuRef(T &menu) : m_menu{menu} {}

protected:
    T &m_menu;
};

class EmptyMenuItem :
    public MenuItem,
    public EmptyText
{
public:
    void triggered() override {}
};
} // namespace espgui
