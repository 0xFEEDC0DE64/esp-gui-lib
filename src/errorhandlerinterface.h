#pragma once

// system includes
#include <string>

namespace espgui {

class ErrorHandlerInterface
{
public:
    virtual void errorOccured(std::string &&error) = 0;
};

class DummyErrorHandler : public virtual ErrorHandlerInterface
{
public:
    void errorOccured(std::string &&error) override {}
};

} // namespace espgui
