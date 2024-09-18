#pragma once

// system includes
#include <format>

// 3rdparty lib includes
#include <strutils.h>
#include <espstrutils.h>
#include <espwifiutils.h>
#include <espchrono.h>

// local includes
#include "textinterface.h"
#include "richtexthelper.h"
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
        using espchrono::toString;
        using wifi_stack::toString;

        return std::format("{} {}", Tprefix, richTextEscape(toString(Taccessor::getValue())));
    }
};

template<typename Taccessor>
struct ChangeableTextWithValueHelper : public Taccessor, public virtual TextInterface
{
    using Taccessor::Taccessor;

    std::string text() const override
    {
        using cpputils::toString;
        using espcpputils::toString;
        using espchrono::toString;
        using wifi_stack::toString;

        return std::format("{} {}", m_prefix, richTextEscape(toString(Taccessor::getValue())));
    }

    const std::string &prefix() const { return m_prefix; }
    void setPrefix(std::string_view prefix) { m_prefix = std::string{prefix}; }
    void setPrefix(std::string &&prefix) { m_prefix = std::move(prefix); }

private:
    std::string m_prefix;
};

template<const char *Tprefix, typename Taccessor, const char *Tguilib_color = espgui::colors::GREY>
struct TextWithHighlightedValueHelper : public Taccessor, public virtual TextInterface
{
    using Taccessor::Taccessor;

    std::string text() const override
    {
        using cpputils::toString;
        using espcpputils::toString;
        using espchrono::toString;
        using wifi_stack::toString;

        return std::format("{} {}{}", Tprefix, Tguilib_color, richTextEscape(toString(Taccessor::getValue())));
    }
};

template<typename Taccessor, const char *Tguilib_color = espgui::colors::GREY>
struct ChangeableTextWithHighlightedValueHelper : public Taccessor, public virtual TextInterface
{
    using Taccessor::Taccessor;

    std::string text() const override
    {
        using cpputils::toString;
        using espcpputils::toString;
        using espchrono::toString;
        using wifi_stack::toString;

        return std::format("{} {}{}", m_prefix, Tguilib_color, richTextEscape(toString(Taccessor::getValue())));
    }

    const std::string &prefix() const { return m_prefix; }
    void setPrefix(std::string_view prefix) { m_prefix = std::string{prefix}; }
    void setPrefix(std::string &&prefix) { m_prefix = std::move(prefix); }

private:
    std::string m_prefix;
};

} // namespace espgui
