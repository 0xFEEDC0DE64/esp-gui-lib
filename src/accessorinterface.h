#pragma once

// system includes
#include <string>
#include <expected>

namespace espgui {
template<typename T>
struct AccessorInterface
{
    using setter_result_t = std::expected<void, std::string>;

    virtual T getValue() const = 0;
    virtual setter_result_t setValue(T value) = 0;
};

//! A special type of AccessorInterface that allows for simple variable read/write operations
//! Can be used to read and write global settings for example.
template<typename T>
struct RefAccessor : public virtual AccessorInterface<T>
{
    virtual T& getRef() const = 0;

    T getValue() const override { return getRef(); };
    std::expected<void, std::string> setValue(T value) override { getRef() = value; return {}; };
};
} // namespace espgui
