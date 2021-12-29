#pragma once

// 3rdparty lib includes
#include <fmt/core.h>
#include <strutils.h>
#include <espstrutils.h>
#include <espwifiutils.h>

// local includes
#include "textinterface.h"
#include "richtextrenderer.h"

namespace espgui {

template<const char *Tprefix, typename Taccessor>
struct TextWithValueHelper : public virtual TextInterface
{
    std::string text() const override
    {
        using cpputils::toString;
        using espcpputils::toString;
        using wifi_stack::toString;

        return fmt::format("{} {}", Tprefix, richTextEscape(toString(Taccessor{}.getValue())));
    }
};

} // namespace espgui
