#pragma once

#include "sdkconfig.h"

// system includes
#include <array>
#include <algorithm>
#include <functional>
#include <cassert>
#include <memory>

// local includes
#include "displaywithtitle.h"
#include "textinterface.h"
#include "widgets/label.h"
#include "menuitem.h"
#include "backinterface.h"

namespace espgui {
class MenuDisplay :
    public DisplayWithTitle,
    public virtual BackInterface
{
    using Base = DisplayWithTitle;

public:
    void start() override;
    void initScreen() override;
    void update() override;
    void redraw() override;
    void stop() override;

    void buttonPressed(Button button) override;
    void buttonReleased(Button button) override;

    MenuDisplay *asMenuDisplay() override { return this; }
    const MenuDisplay *asMenuDisplay() const override { return this; }

    int selectedIndex() const { return m_selectedIndex; }


    std::size_t menuItemCount() const { return m_menuItems.size(); }

    MenuItem& getMenuItem(std::size_t index)
    {
        assert(index < m_menuItems.size());
        return *m_menuItems[index].get();
    }

    const MenuItem& getMenuItem(std::size_t index) const
    {
        assert(index < m_menuItems.size());
        return *m_menuItems[index].get();
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback)
    {
        for (const auto &ptr : m_menuItems)
            callback(*ptr);
    }

    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const
    {
        for (const auto &ptr : m_menuItems)
            callback(*ptr);
    }

    template<typename T, typename... Args>
    T &constructMenuItem(Args&&... args)
    {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T &ref = *ptr;
        emplaceMenuItem(std::move(ptr));
        return ref;
    }

    void emplaceMenuItem(std::unique_ptr<MenuItem> &&ptr)
    {
        m_menuItems.emplace_back(std::move(ptr));
    }

    void clearMenuItems()
    {
        m_menuItems.clear();
    }

    std::unique_ptr<MenuItem> takeLastMenuItem()
    {
        assert(!m_menuItems.empty());
        std::unique_ptr<MenuItem> ptr = std::move(m_menuItems.back());
        m_menuItems.pop_back();
        return ptr;
    }

protected:
    void setSelectedIndex(int selectedIndex) { m_selectedIndex = selectedIndex; }

private:
    static constexpr size_t rowCount = CONFIG_ESPGUI_MENUDISPLAY_ROWS;
    static constexpr auto iconWidth = 25;
    static constexpr auto horizontalSpacing = 10;
    static constexpr auto topMargin = 39;
    static constexpr auto lineHeight = 27;
    static constexpr auto verticalSpacing = 2;

    std::array<Label, rowCount> m_labels {{
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 1
        Label{horizontalSpacing + iconWidth, topMargin+(0*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 2
        Label{horizontalSpacing + iconWidth, topMargin+(1*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 3
        Label{horizontalSpacing + iconWidth, topMargin+(2*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 4
        Label{horizontalSpacing + iconWidth, topMargin+(3*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 5
        Label{horizontalSpacing + iconWidth, topMargin+(4*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 6
        Label{horizontalSpacing + iconWidth, topMargin+(5*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 7
        Label{horizontalSpacing + iconWidth, topMargin+(6*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 8
        Label{horizontalSpacing + iconWidth, topMargin+(7*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 9
        Label{horizontalSpacing + iconWidth, topMargin+(8*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
#if CONFIG_ESPGUI_MENUDISPLAY_ROWS >= 10
        Label{horizontalSpacing + iconWidth, topMargin+(9*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
#endif
    }};

    std::array<const Icon<24, 24> *, rowCount> m_icons;

    int m_selectedIndex;
    int m_scrollOffset;
    int m_highlightedIndex;

    int m_rotateOffset;
    bool m_pressed;

    std::vector<std::unique_ptr<MenuItem>> m_menuItems;
};
} // namespace espgui
