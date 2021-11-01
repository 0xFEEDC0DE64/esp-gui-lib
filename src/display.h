#pragma once

// system includes
#include <string>

// forward declares
namespace espgui {
class TextInterface;
class MenuDisplay;
class ChangeValueDisplayInterface;
}

namespace espgui {
template<typename ...T>
class makeComponent : public T...
{};

template <typename T1, typename T2, typename ...T3>
class makeComponentArgs : public T1, public T2, public T3...
{
public:
    template<typename ...T>
    makeComponentArgs(T&& ...args) :
        T2{std::forward<T>(args)...}
    {
    }
};

class ConfirmInterface
{
public:
    virtual void confirm() = 0;
};

class BackInterface
{
public:
    virtual void back() = 0;
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

template<typename T>
class BackActionInterface : public virtual BackInterface
{
public:
    void back() override { T{}.triggered(); }
};

class DummyBack : public virtual BackInterface
{
public:
    void back() override {}
};

class Display :
    public virtual ConfirmInterface,
    public virtual BackInterface
{
public:
    virtual ~Display() = default;

    virtual void start() {}
    virtual void initScreen();
    virtual void update() {}
    virtual void redraw() {}
    virtual void stop() {}

    virtual void rotate(int offset) {}

    virtual TextInterface *asTextInterface() { return nullptr; }
    virtual const TextInterface *asTextInterface() const { return nullptr; }

    virtual MenuDisplay *asMenuDisplay() { return nullptr; }
    virtual const MenuDisplay *asMenuDisplay() const { return nullptr; }

    virtual ChangeValueDisplayInterface *asChangeValueDisplayInterface() { return nullptr; }
    virtual const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const { return nullptr; }
};
} // namespace espgui
