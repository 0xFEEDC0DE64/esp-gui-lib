#include "menudisplay.h"

// local includes
#include "tftinstance.h"

namespace espgui {
void MenuDisplay::start()
{
    Base::start();

//    m_selectedIndex = 0;
//    m_scrollOffset = 0;

    m_rotateOffset = 0;
    m_pressed = false;
}

void MenuDisplay::initScreen()
{
    Base::initScreen();

    for (auto &label : m_labels)
        label.start();

    runForEveryMenuItem([](MenuItem &item){
        item.start();
    });

    m_icons.fill(nullptr);

    m_highlightedIndex = -1;
}

void MenuDisplay::update()
{
    Base::update();

    if (!m_pressed)
    {
        const auto offset = m_rotateOffset;
        m_rotateOffset = 0;

        const auto itemCount = menuItemCount();

        if (itemCount)
        {
            if (m_selectedIndex == -1)
                m_selectedIndex = 0;

            m_selectedIndex = m_selectedIndex + offset;

            if (m_selectedIndex < 0)
                m_selectedIndex += itemCount;
            if (m_selectedIndex >= itemCount)
                m_selectedIndex -= itemCount;

            if (m_selectedIndex < m_scrollOffset)
                m_scrollOffset = m_selectedIndex;
            if (m_selectedIndex >= m_scrollOffset + m_labels.size())
                m_scrollOffset = m_selectedIndex - m_labels.size() + 1;
        }
        else
        {
            m_selectedIndex = -1;
            m_scrollOffset = 0;
        }

        runForEveryMenuItem([&](MenuItem &item){
            item.update();
        });

        if (getMenuItem(m_selectedIndex).skipScroll())
        {
            if (offset > 0)
            {
                m_rotateOffset++;
            }
            else if (offset < 0)
            {
                m_rotateOffset--;
            }
        }
    }
    else
    {
        m_pressed = false;
        if (m_selectedIndex >= 0)
            getMenuItem(m_selectedIndex).triggered();
    }
}

void MenuDisplay::redraw()
{
    Base::redraw();

    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);

    int i{0};

    auto labelsIter = std::begin(m_labels);

    auto iconsIter = std::begin(m_icons);

    int newHighlightedIndex{-1};

    const auto drawItemRect = [](const auto &label, const auto color){
        tft.drawRect(5,
                     label.y()-1,
                     tft.width() - 10,
                     lineHeight+1,
                     color);
    };

    runForEveryMenuItem([&](MenuItem &item){
        const auto index = i++;

        if (!item.visible())
        {
            return;
        }

        if (index < m_scrollOffset)
            return;

        if (labelsIter == std::end(m_labels))
            return;

        const auto relativeIndex = index - m_scrollOffset;
        const auto selected = index == m_selectedIndex;

        if (selected)
            newHighlightedIndex = relativeIndex;
        else if (relativeIndex == m_highlightedIndex)
            drawItemRect(*labelsIter, TFT_BLACK);

        tft.setTextFont(item.font());
        tft.setTextColor(item.color(), TFT_BLACK);
        labelsIter->redraw(item.text());

        if (item.icon() != *iconsIter)
        {
            tft.fillRect(6, labelsIter->y()+1, 24, 24, TFT_BLACK);

            auto icon = item.icon();
            if (icon)
            {
                tft.setSwapBytes(true);
                tft.pushImage(6, labelsIter->y()+1, icon->WIDTH, icon->HEIGHT, icon->buffer);
                tft.setSwapBytes(false);
            }
            *iconsIter = icon;
        }

        if (selected && (relativeIndex != m_highlightedIndex))
        {
            drawItemRect(*labelsIter, TFT_WHITE);
        }

        labelsIter++;
        iconsIter++;
    });

    for (; labelsIter != std::end(m_labels); labelsIter++, iconsIter++)
    {
        const auto relativeIndex = std::distance(std::begin(m_labels), labelsIter);

        if (relativeIndex == m_highlightedIndex)
            drawItemRect(*labelsIter, TFT_BLACK);

        labelsIter->clear();

        if (*iconsIter)
        {
            tft.fillRect(5, labelsIter->y()+1, 24, 24, TFT_BLACK);
            *iconsIter = nullptr;
        }
    }

    m_highlightedIndex = newHighlightedIndex;
}

void MenuDisplay::stop()
{
    Base::stop();

    runForEveryMenuItem([](MenuItem &item){
        item.stop();
    });
}

void MenuDisplay::buttonPressed(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Left: this->back(); break;
    case Button::Right: m_pressed = true; break;
    case Button::Up: m_rotateOffset--; break;
    case Button::Down: m_rotateOffset++; break;
    }
}

void MenuDisplay::buttonReleased(Button button)
{
    //Base::buttonPressed(button);
    // TODO stop auto scroll
}
} // namespace espgui
