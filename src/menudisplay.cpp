#include "menudisplay.h"

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

using namespace std::chrono_literals;

namespace espgui {
void MenuDisplay::start()
{
    Base::start();

//    m_selectedIndex = 0;
//    m_scrollOffset = 0;

    m_rotateOffset = 0;
    m_pressed = false;

    m_upHeld = std::nullopt;
    m_downHeld = std::nullopt;
}

void MenuDisplay::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    for (auto &label : m_labels)
        label.start(tft);

    runForEveryMenuItem([](MenuItem &item){
        item.start();
    });

    m_icons.fill(nullptr);

    m_highlightedIndex = -1;
}

void MenuDisplay::update()
{
    Base::update();

    const auto now = espchrono::millis_clock::now();
    if (m_upHeld && now >= m_upHeld->nextTimestamp)
    {
        m_upHeld->nextTimestamp += m_upHeld->counter > 3 ? 100ms : 200ms;
        m_upHeld->counter++;
        m_rotateOffset--;
    }
    if (m_downHeld && now >= m_downHeld->nextTimestamp)
    {
        m_downHeld->nextTimestamp += m_downHeld->counter > 3 ? 100ms : 200ms;
        m_downHeld->counter++;
        m_rotateOffset++;
    }

    {
        const auto offset = m_rotateOffset;
        m_rotateOffset = 0;

        if (const auto itemCount = menuItemCount())
        {
            if (m_selectedIndex == -1)
                m_selectedIndex = 0;

            m_selectedIndex += offset;

            if (m_selectedIndex < 0)
                m_selectedIndex += itemCount;
            if (m_selectedIndex >= itemCount)
                m_selectedIndex -= itemCount;

            if (getMenuItem(m_selectedIndex).skipScroll())
            {
                m_selectedIndex = offset >= 0 ?
                    getNextAccessibleMenuItemIndex(m_selectedIndex) :
                getPreviousAccessibleMenuItemIndex(m_selectedIndex);
            }

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
    }

    if (m_pressed)
    {
        m_pressed = false;
        if (m_selectedIndex >= 0 && m_selectedIndex < m_menuItems.size())
            getMenuItem(m_selectedIndex).triggered();
    }
}

void MenuDisplay::redraw(TftInterface &tft)
{
    Base::redraw(tft);

    int i{0};

    auto labelsIter = std::begin(m_labels);

    auto iconsIter = std::begin(m_icons);

    int newHighlightedIndex{-1};

    const auto drawItemRect = [&tft](const auto &label, const auto color){
        tft.fillRect(5,
                     label.y()-1,
                     tft.width() - 10,
                     lineHeight+1,
                     color);
        //tft.drawRoundRect(5,
        //                  label.y()-1,
        //                  tft.width() - 10,
        //                  lineHeight+1,
        //                  5,
        //                  color);
    };

    runForEveryMenuItem([&](MenuItem &item){
        const auto index = i++;

        if (!item.visible())
            return;

        if (index < m_scrollOffset)
            return;

        if (labelsIter == std::end(m_labels))
            return;

        const auto relativeIndex = index - m_scrollOffset;
        const auto selected = index == m_selectedIndex;

        if (selected)
        {
            newHighlightedIndex = relativeIndex;

            if (relativeIndex != m_highlightedIndex)
            {
                drawItemRect(*labelsIter, TFT_GREY);
                *iconsIter = nullptr;
                labelsIter->start(tft);

                if (auto icon = item.selectedIcon())
                {
                    tft.pushImage(tft.width() - 6 - icon->WIDTH, labelsIter->y() + 1, *icon);
                }
            }
        }
        else if (relativeIndex == m_highlightedIndex)
        {
            drawItemRect(*labelsIter, TFT_BLACK);
            *iconsIter = nullptr;
            labelsIter->start(tft);
        }

        labelsIter->redraw(tft, item.text(), item.color(), selected ? TFT_GREY : TFT_BLACK, item.font());

        if (const auto icon = item.icon(selected); icon != *iconsIter)
        {
            if (icon)
                tft.pushImage(6, labelsIter->y() + 1, *icon);
            else if (*iconsIter)
                tft.fillRect(6, labelsIter->y() + 1, 24, 24, selected ? TFT_GREY : TFT_BLACK);
            *iconsIter = icon;
        }

//        if (selected && (relativeIndex != m_highlightedIndex))
//        {
//            drawItemRect(*labelsIter, TFT_GREY);
//        }

        labelsIter++;
        iconsIter++;
    });

    for (; labelsIter != std::end(m_labels); labelsIter++, iconsIter++)
    {
        const auto relativeIndex = std::distance(std::begin(m_labels), labelsIter);

        if (relativeIndex == m_highlightedIndex)
            drawItemRect(*labelsIter, TFT_BLACK);

        labelsIter->clear(tft, TFT_BLACK);

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
    case Button::Up:
        m_rotateOffset--;
        m_upHeld = ButtonHeldInfo { .nextTimestamp = espchrono::millis_clock::now() + 300ms };
        break;
    case Button::Down:
        m_rotateOffset++;
        m_downHeld = ButtonHeldInfo { .nextTimestamp = espchrono::millis_clock::now() + 300ms };
        break;
    }
}

void MenuDisplay::buttonReleased(Button button)
{
    //Base::buttonPressed(button);

    switch (button)
    {
    case Button::Up:
        m_upHeld = std::nullopt;
        break;
    case Button::Down:
        m_downHeld = std::nullopt;
        break;
    default:;
    }
}
} // namespace espgui
