#pragma once

// local includes
#include "icon.h"

namespace espgui {

template<uint16_t width, uint16_t height>
class IconInterface
{
public:
    virtual const Icon<width, height> *icon() const { return nullptr; }
};

template<uint16_t width, uint16_t height>
class SelectedIconInterface
{
public:
    virtual const Icon<width, height> *selectedIcon() const { return nullptr; }
};

template<uint16_t width, uint16_t height, const Icon<width, height> *T>
class StaticIcon : public virtual IconInterface<width, height>
{
public:
    virtual const Icon<width, height> *icon() const { return T; }
};

template<uint16_t width, uint16_t height, const Icon<width, height> *T>
class StaticSelectedIcon : public virtual SelectedIconInterface<width, height>
{
public:
    virtual const Icon<width, height> *selectedIcon() const { return T; }
};

} // namespace espgui
