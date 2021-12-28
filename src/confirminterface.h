#pragma once

namespace espgui {

class ConfirmInterface
{
public:
    virtual void confirm() = 0;
};

template<typename T>
class ConfirmActionInterface : public virtual ConfirmInterface
{
public:
    void confirm() override { T{}.triggered(); }
};

class DummyConfirm : public virtual ConfirmInterface
{
public:
    void confirm() override {}
};

} // namespace espgui
