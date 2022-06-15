#pragma once

// system includes
#include <string>

namespace espgui {

class ErrorHandlerInterface
{
public:
    virtual void errorOccurred(std::string &&error) = 0;
};

class DummyErrorHandler : public virtual ErrorHandlerInterface
{
public:
    void errorOccurred(std::string &&error) override {}
};

} // namespace espgui
