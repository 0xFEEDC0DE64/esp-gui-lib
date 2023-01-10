#pragma once

// system includes
#include <string>
#include <utility>

namespace espgui {

class TitleInterface {
public:
    virtual std::string title() const = 0;
};

class EmptyTitle : public virtual TitleInterface
{
public:
    std::string title() const override { return {}; }
};

template<const char *Ttitle>
class StaticTitle : public virtual TitleInterface
{
public:
    static constexpr const char *STATIC_TITLE = Ttitle;

    std::string title() const override { return Ttitle; }
};

class ChangeableTitle : public virtual TitleInterface
{
public:
    ChangeableTitle() = default;
    ChangeableTitle(std::string &&title) : m_title{std::move(title)} {}
    ChangeableTitle(std::string_view title) : m_title{title} {}

    std::string title() const override { return m_title; }
    void setTitle(std::string &&title) { m_title = std::move(title); }
    void setTitle(const std::string &title) { m_title = title; }

private:
    std::string m_title;
};

template<typename T>
class CachedTitle : public virtual T
{
public:
    std::string title() const override
    {
        if (!m_loaded)
        {
            m_title = T::title();
            m_loaded = true;
        }

        return m_title;
    }

private:
    mutable bool m_loaded{};
    mutable std::string m_title;
};

template<typename T>
class StaticallyCachedTitle : public virtual T
{
public:
    std::string title() const override
    {
        static const auto title = T::title();
        return title;
    }
};

} // namespace espgui
