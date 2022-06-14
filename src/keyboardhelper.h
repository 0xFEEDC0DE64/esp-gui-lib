#pragma once

// system includes
#include <futurecpp.h>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <fmt/core.h>
#include <strutils.h>

// local includes
#include "display.h"
#include "screenmanager.h"
#include "tftinstance.h"

namespace espgui {
namespace {
    constexpr const char * const TAG = "KeyboardHelper";
    // all ascii chars from '!' to '~'
    constexpr const char * const KEYBOARD_SCREEN_1 =  "\"!$%&/()=?QWERTZUIOPASDFGHJKL YXCVBNM";
    constexpr const char * const KEYBOARD_SCREEN_2 =   "1234567890qwertzuiopasdfghjkl yxcvbnm";
    constexpr const char * const KEYBOARD_SCREEN_3 = "#'*+-,.;:_<|>\\@[]^_`{}~\"!$%&/ ()=?+-*";
    constexpr const char * const SHIFT = "Shift";
    constexpr const char * const SPACE = "Space";
    constexpr const char * const BACKSPACE = "Back";
    constexpr const char * const ENTER = "Enter";
} // namespace

template<typename TDisplay = espgui::Display>
class Keyboard
{
public:
    explicit Keyboard(TDisplay &display) : m_display(display) {}

    void start();

    void buttonPressed(Button button);
    void buttonReleased(Button button);

    void moveSelectorUp();
    void moveSelectorDown();
    void moveSelectorLeft();
    void moveSelectorRight();

private:
    void updateCharLength();

    void drawKeyboard(bool dont_draw_string = false);

    void nextScreen();

    int32_t m_char_length{0};
    std::string m_keyboard{KEYBOARD_SCREEN_1};
    std::string m_keyset{};

    TDisplay &m_display;
    int32_t m_keyboard_start_y{0};

    int32_t m_char_index{10};
    int32_t m_last_char_index{-1};

    enum class Screen : uint8_t {
        SCREEN_1,
        SCREEN_2,
        SCREEN_3,
        SCREEN_MAX
    };
    Screen m_current_screen{Screen::SCREEN_2};
};

template<typename TDisplay>
void Keyboard<TDisplay>::moveSelectorUp()
{
    m_last_char_index = m_char_index;

    m_char_index -= 10;
    if (m_char_index < 0)
        m_char_index = (m_char_length + 4) - m_char_index;
}

template<typename TDisplay>
void Keyboard<TDisplay>::moveSelectorDown()
{
    m_last_char_index = m_char_index;

    m_char_index += 10;
    if (m_char_index >= (m_char_length + 4))
        m_char_index = m_char_index - (m_char_length + 4);
}

template<typename TDisplay>
void Keyboard<TDisplay>::nextScreen()
{
    m_current_screen = static_cast<Screen>(static_cast<uint8_t>(m_current_screen) + uint8_t{1});
    if (m_current_screen >= Screen::SCREEN_MAX)
        m_current_screen = Screen::SCREEN_1;
    updateCharLength();
    start();
}

template<typename TDisplay>
void Keyboard<TDisplay>::drawKeyboard(bool dont_draw_string)
{
    size_t char_index{0};
    std::string keyboard_screen{m_keyboard};

    std::vector<std::string> keyboard_lines;

    for (size_t i = 0; i < keyboard_screen.size(); i += 10)
    {
        std::string line = keyboard_screen.substr(i, 10);
        if (cpputils::stringEndsWith(line, " "))
            line.pop_back();

        keyboard_lines.push_back(line);
    }

    const auto datum = tft.getTextDatum();
    tft.setTextDatum(MC_DATUM);

    for (size_t i = 0; i < keyboard_lines.size(); i++)
    {                tft.setTextColor(TFT_WHITE);

        tft.setTextColor(TFT_GREY);

        const int32_t y = m_keyboard_start_y + (i * tft.fontHeight() + 9);
        std::string line = keyboard_lines[i];
        const int16_t x = tft.width() / (line.size() + 1);
        for (size_t j = 0; j < line.size(); j++)
        {
            const std::string _char{line[j]};
            const int32_t x_pos = x * (j + 1);
            const int32_t y_pos = y;

            const auto width = tft.textWidth(_char) + 2;
            const auto height = tft.fontHeight() + 4;
            if (char_index == m_char_index)
                tft.drawRoundRect(x_pos-width/2-1, y_pos-height/2, width+2, height-4, 3, TFT_DARKGREY);

            if (char_index == m_last_char_index)
            {
                tft.drawRoundRect(x_pos-width/2-1, y_pos-height/2, width+2, height-4, 3, TFT_BLACK);
            }

            if (!dont_draw_string || char_index == m_char_index || char_index == m_last_char_index)
            {
                if (char_index == m_char_index || char_index == m_last_char_index)
                    tft.setTextColor(char_index == m_last_char_index ? TFT_GREY : TFT_WHITE);

                tft.drawString(_char, x_pos, y_pos);

                if (char_index == m_char_index)
                    tft.setTextColor(TFT_GREY);
            }
            char_index++;
        }
    }

    tft.setTextDatum(datum);

    // draw 3 extra buttons, back, space and enter (x=10, x=tft.width()/2, x=tft.width()-10)
    const int32_t y = m_keyboard_start_y + (keyboard_lines.size() * tft.fontHeight());

    if (isLandscape())
    {
        // align left (SHIFT, SPACE)
        tft.drawRoundRect(15 - 2, y - 1, tft.textWidth(SHIFT) + 4, tft.fontHeight() + 2, 3, TFT_DARKGREY);
        tft.drawRoundRect(30 + tft.textWidth(SHIFT) - 2, y - 1, tft.textWidth(SPACE) + 4, tft.fontHeight() + 2, 3,
                          TFT_DARKGREY);

        // align right (BACKSPACE, ENTER); align from tft.width()
        tft.drawRoundRect(tft.width() - 30 - tft.textWidth(ENTER) - tft.textWidth(BACKSPACE) - 2, y - 1,
                          tft.textWidth(BACKSPACE) + 4, tft.fontHeight() + 2, 3, TFT_DARKGREY);
        tft.drawRoundRect(tft.width() - 15 - tft.textWidth(ENTER) - 2, y - 1, tft.textWidth(ENTER) + 4,
                          tft.fontHeight() + 2, 3, TFT_DARKGREY);

        // if (!dont_draw_string)
        {
            // align left (SHIFT, SPACE)
            if (m_char_index == m_char_length)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(SHIFT, 15, y);

            if (m_char_index == m_char_length + 1)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(SPACE, 30 + tft.textWidth(SHIFT), y);

            // align right (BACKSPACE, ENTER); align from tft.width()
            if (m_char_index == m_char_length + 2)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(BACKSPACE, tft.width() - 30 - tft.textWidth(ENTER) - tft.textWidth(BACKSPACE), y);

            if (m_char_index == m_char_length + 3)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(ENTER, tft.width() - 15 - tft.textWidth(ENTER), y);
        }
    }
    else
    {
        const int32_t y_2 = y + tft.fontHeight() + 4;
        // align left (SHIFT, SPACE)
        tft.drawRoundRect(15 - 2,   y - 1, tft.textWidth(SHIFT) + 4, tft.fontHeight() + 2, 3, TFT_DARKGREY);
        tft.drawRoundRect(15 - 2, y_2 - 1, tft.textWidth(SPACE) + 4, tft.fontHeight() + 2, 3, TFT_DARKGREY);

        // align right (BACKSPACE, ENTER); align from tft.width()
        tft.drawRoundRect(tft.width() - 15 - tft.textWidth(ENTER) - 2, y - 1, tft.textWidth(ENTER) + 4,
                          tft.fontHeight() + 2, 3, TFT_DARKGREY);
        tft.drawRoundRect(tft.width() - 15 - tft.textWidth(BACKSPACE) - 2, y_2 - 1, tft.textWidth(BACKSPACE) + 4,
                          tft.fontHeight() + 2, 3, TFT_DARKGREY);

        // if (!dont_draw_string)
        {
            // align left (SHIFT, SPACE)
            if (m_char_index == m_char_length)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(SHIFT, 15, y);

            if (m_char_index == m_char_length + 1)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(SPACE, 15, y_2);

            // align right (BACKSPACE, ENTER); align from tft.width()
            if (m_char_index == m_char_length + 2)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(BACKSPACE, tft.width() - 15 - tft.textWidth(BACKSPACE), y_2);

            if (m_char_index == m_char_length + 3)
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
            else
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString(ENTER, tft.width() - 15 - tft.textWidth(ENTER), y);
        }
    }
}

template<typename TDisplay>
void Keyboard<TDisplay>::updateCharLength()
{
    std::string tmpstr;

    switch (m_current_screen)
    {
    case Screen::SCREEN_1:
        tmpstr = KEYBOARD_SCREEN_1;
        break;
    case Screen::SCREEN_2:
        tmpstr = KEYBOARD_SCREEN_2;
        break;
    case Screen::SCREEN_3:
        tmpstr = KEYBOARD_SCREEN_3;
        break;
    default:
        ESP_LOGE(TAG, "Unknown screen");
        return;
    }

    m_keyboard = tmpstr;
    cpputils::stringReplaceAll(" ", "", tmpstr);
    m_char_length = tmpstr.length();
    m_keyset = tmpstr;
}

template<typename TDisplay>
void Keyboard<TDisplay>::moveSelectorRight()
{
    m_last_char_index = m_char_index;

    if (m_char_index == (m_char_length + 4) - 1)
        m_char_index = 0;
    else
        m_char_index++;
}

template<typename TDisplay>
void Keyboard<TDisplay>::moveSelectorLeft()
{
    m_last_char_index = m_char_index;

    if (m_char_index == 0)
        m_char_index = (m_char_length + 4) - 1;
    else
        m_char_index--;
}

template<typename TDisplay>
void Keyboard<TDisplay>::start()
{
    const auto isLandscape = espgui::isLandscape();
    m_keyboard_start_y = isLandscape ? 98 : 120;

    tft.fillRect(1, m_keyboard_start_y - 10, tft.width()-1, tft.height() - m_keyboard_start_y - (isLandscape ? 0 : 30), TFT_BLACK);
    tft.drawSunkenRect(1, m_keyboard_start_y - 10, tft.width()-1, tft.height() - m_keyboard_start_y - (isLandscape ? 0 : 30), TFT_WHITE, TFT_GREY, TFT_BLACK);

    updateCharLength();
    drawKeyboard();
}

template<typename TDisplay>
void Keyboard<TDisplay>::buttonPressed(Button button)
{
    switch (button)
    {
    case Right:
    {
        if (m_char_index < m_char_length)
            m_display.setShownValue(m_display.shownValue() + m_keyset[m_char_index]);
        else if (m_char_index == m_char_length) // shift
        {
            nextScreen();
        }
        else if (m_char_index == m_char_length + 1) // space
        {
            m_display.setShownValue(m_display.shownValue() + " ");
        }
        else if (m_char_index == m_char_length + 2) // backspace
        {
            m_display.removeLastCharFromShownValue();
        }
        else if (m_char_index == m_char_length + 3) // enter
        {
            m_display.confirmValue();
        }
        break;
    }
    case Left:
        popScreen();
        return;
    case Up:
        moveSelectorLeft();
        drawKeyboard(true);
        break;
    case Down:
        moveSelectorRight();
        drawKeyboard(true);
        break;
    default:;
    }
}

template<typename TDisplay>
void Keyboard<TDisplay>::buttonReleased(espgui::Button button) {}
} // namespace espgui
