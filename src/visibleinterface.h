#pragma once

namespace espgui {
class VisibleInterface {
public:
    virtual bool visible() const { return true; }
};

template<bool TVisible>
class StaticVisibility : public virtual VisibleInterface
{
public:
    bool visible() const override { return TVisible; }
};

class ChangeableVisibility : public virtual VisibleInterface
{
public:
    void setVisible(bool visible) { m_visible = visible; }
    bool visible() const override { return m_visible; }
private:
    bool m_visible = true;
};
} // namespace espgui
