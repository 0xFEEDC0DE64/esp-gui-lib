#pragma once

// 3rdparty lib includes
#include <fmt/core.h>
#include <strutils.h>
#include <espstrutils.h>
#include <espwifiutils.h>
#include <espchrono.h>

// local includes
#include "textinterface.h"
#include "richtextrenderer.h"

namespace espgui {

template<const char *Tprefix, typename Taccessor>
struct TextWithValueHelper : public Taccessor, public virtual TextInterface
{
    using Taccessor::Taccessor;

    std::string text() const override
    {
        using cpputils::toString;
        using espcpputils::toString;
        using wifi_stack::toString;
        using espchrono::toString;

        return fmt::format("{} {}", Tprefix, richTextEscape(toString(Taccessor::getValue())));
    }
};

} // namespace espgui
