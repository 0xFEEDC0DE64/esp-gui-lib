#pragma once

// system includes
#include <string>
#include <optional>

// local includes
#include "backinterface.h"
#include "changevaluedisplay.h"
#include "confirminterface.h"
#include "displaywithtitle.h"
#include "errorhandlerinterface.h"
#include "keyboardhelper.h"
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
    void initScreen(TftInterface &tft) override;
    void redraw(TftInterface &tft) override;

    void buttonPressed(Button button) override;
    void buttonReleased(Button button) override;

    void confirmValue();

    const std::string &shownValue() const { return m_value; }
    void setShownValue(std::string &&value);
    void appendToShownValue(char c) { m_value.push_back(c); }
    void appendToShownValue(const std::string &s) { m_value.append(s); }
    void removeLastCharFromShownValue();

private:
    std::string m_value;

    Label m_valueLabel{12, 55}; // 188, 53
    Keyboard<ChangeValueDisplay<std::string>> m_keyboard{*this};

    std::optional<std::string> m_needsClear;
};

} // namespace espgui
