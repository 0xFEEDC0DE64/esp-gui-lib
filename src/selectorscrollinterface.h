#pragma once

// 3rdparty lib includes
#include <espchrono.h>

namespace espgui {
namespace {
template <typename T>
struct is_allowed
{
    static constexpr bool value = false;
};

template <>
struct is_allowed<espchrono::milliseconds32>
{
    static constexpr bool value = true;
};
template <>
struct is_allowed<espchrono::seconds32>
{
    static constexpr bool value = true;
};
template <>
struct is_allowed<espchrono::minutes32>
{
    static constexpr bool value = true;
};
template <>
struct is_allowed<espchrono::hours32>
{
    static constexpr bool value = true;
};
} // namespace

template<typename TimeType = espchrono::milliseconds32, int initialDelay = 750, int delay = 150>
class SelectorScrollInterface {
    static_assert(is_allowed<TimeType>::value, "Type not supported");
public:
    TimeType getInitialScrollSpeed() const { return initialScrollDelay; }
    TimeType getScrollSpeed() const { return scrollDelay; }

    void setInitialScrollSpeed(TimeType speed) { initialScrollDelay = speed; }
    void setScrollSpeed(TimeType speed) { scrollDelay = speed; }

private:
    TimeType initialScrollDelay{initialDelay};
    TimeType scrollDelay{delay};
};
} // namespace espgui
