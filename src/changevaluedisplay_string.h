#pragma once

// local includes
#include "changevaluedisplay.h"
#include "displaywithtitle.h"
#include "confirminterface.h"
#include "backinterface.h"
#include "errorhandlerinterface.h"
#include "widgets/label.h"

namespace espgui {

template<>
class ChangeValueDisplay<std::string> :
    public DisplayWithTitle,
    public virtual AccessorInterface<std::string>,
    public virtual ConfirmInterface,
    public virtual BackInterface,
    public virtual ErrorHandlerInterface
{
    using Base = DisplayWithTitle;

public:
    ChangeValueDisplay<std::string> *asChangeValueDisplayString() override { return this; }
    const ChangeValueDisplay<std::string> *asChangeValueDisplayString() const override { return this; }

    void start() override;
    void initScreen() override;
    void update() override;
    void redraw() override;

    void buttonPressed(Button button) override;

    const std::string &shownValue() const { return m_value; }
    void setShownValue(std::string &&value) { m_value = std::move(value); }

private:
    std::string m_value;
    bool m_pressed{};

    Label m_valueLabel{26, 81}; // 188, 53
};

} // namespace espgui
