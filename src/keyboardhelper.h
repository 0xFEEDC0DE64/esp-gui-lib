#pragma once

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <strutils.h>
#include <fontrenderer.h>

// local includes
#include "tftinterface.h"
#include "tftcolors.h"
#include "display.h"
#include "screenmanager.h"

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

    void start(TftInterface &tft);
    void update();
    void redraw(TftInterface &tft);

    void buttonPressed(Button button);
    void buttonReleased(Button button);

    void moveSelectorUp();
    void moveSelectorDown();
    void moveSelectorLeft();
    void moveSelectorRight();

private:
    void updateCharLength();

    void drawKeyboard(TftInterface &tft, bool dont_draw_string = false);

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

    bool m_needsStart{};
    bool m_needsRedraw{};

    std::optional<espchrono::millis_clock::time_point> m_back_pressed_time{};
    std::optional<espchrono::millis_clock::time_point> m_confirm_pressed_time{};

    struct ButtonHeldInfo
    {
        espchrono::millis_clock::time_point nextTimestamp;
        int counter{};
    };

    std::optional<ButtonHeldInfo> m_upHeld;
    std::optional<ButtonHeldInfo> m_downHeld;
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

    m_needsStart = true;
    m_needsRedraw = true;
}

template<typename TDisplay>
void Keyboard<TDisplay>::drawKeyboard(TftInterface &tft, bool dont_draw_string)
{
    FontRenderer fontRenderer{tft};

    constexpr const int FONT = 4;

    size_t char_index{0};
    std::string keyboard_screen{m_keyboard};

    std::vector<std::string> keyboard_lines;

    for (size_t i = 0; i < keyboard_screen.size(); i += 10)
    {
        std::string line = keyboard_screen.substr(i, 10);
        if (line.ends_with(" "))
            line.pop_back();

        keyboard_lines.push_back(line);
    }

    for (size_t i = 0; i < keyboard_lines.size(); i++)
    {
        const int32_t y = m_keyboard_start_y + (i * fontRenderer.fontHeight(FONT) + 9);
        std::string line = keyboard_lines[i];
        const int16_t x = tft.width() / (line.size() + 1);
        for (size_t j = 0; j < line.size(); j++)
        {
            const std::string _char{line[j]};
            const int32_t x_pos = x * (j + 1);
            const int32_t y_pos = y;

            const auto width = fontRenderer.textWidth(_char, FONT) + 2;
            const auto height = fontRenderer.fontHeight(FONT) + 4;

            tft.drawRoundRect(x_pos-width/2-1, y_pos-height/2, width+2, height-4, 3, espgui::TFT_BLACK);

            if (char_index == m_char_index)
                tft.drawRoundRect(x_pos-width/2-1, y_pos-height/2, width+2, height-4, 3, espgui::TFT_DARKGREY);

            if (!dont_draw_string || char_index == m_char_index || char_index == m_last_char_index)
            {
                fontRenderer.drawString(_char, x_pos, y_pos, (char_index == m_char_index ? espgui::TFT_WHITE : espgui::TFT_GREY), espgui::TFT_BLACK, FONT, 4); // 4 = center
            }
            char_index++;
        }
    }

    // draw 3 extra buttons, back, space and enter (x=10, x=tft.width()/2, x=tft.width()-10)
    const int32_t y = m_keyboard_start_y + (keyboard_lines.size() * fontRenderer.fontHeight(FONT));

    if (isLandscape(tft))
    {
        // align left (SHIFT, SPACE)
        tft.drawRoundRect(15 - 2, y - 1, fontRenderer.textWidth(SHIFT, FONT) + 4, fontRenderer.fontHeight(FONT) + 2, 3, espgui::TFT_DARKGREY);
        tft.drawRoundRect(30 + fontRenderer.textWidth(SHIFT, FONT) - 2, y - 1, fontRenderer.textWidth(SPACE, FONT) + 4, fontRenderer.fontHeight(FONT) + 2, 3,
                          espgui::TFT_DARKGREY);

        // align right (BACKSPACE, ENTER); align from tft.width()
        tft.drawRoundRect(tft.width() - 30 - fontRenderer.textWidth(ENTER, FONT) - fontRenderer.textWidth(BACKSPACE, FONT) - 2, y - 1,
                          fontRenderer.textWidth(BACKSPACE, FONT) + 4, fontRenderer.fontHeight(FONT) + 2, 3, espgui::TFT_DARKGREY);
        tft.drawRoundRect(tft.width() - 15 - fontRenderer.textWidth(ENTER, FONT) - 2, y - 1, fontRenderer.textWidth(ENTER, FONT) + 4,
                          fontRenderer.fontHeight(FONT) + 2, 3, espgui::TFT_DARKGREY);

        // if (!dont_draw_string)
        {
            // align left (SHIFT, SPACE)
            fontRenderer.drawString(SHIFT, 15, y, (m_char_index == m_char_length ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);
            fontRenderer.drawString(SPACE, 30 + fontRenderer.textWidth(SHIFT, FONT), y, (m_char_index == m_char_length + 1 ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length +1 ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);

            // align right (BACKSPACE, ENTER); align from tft.width()
            fontRenderer.drawString(BACKSPACE, tft.width() - 30 - fontRenderer.textWidth(ENTER, FONT) - fontRenderer.textWidth(BACKSPACE, FONT), y, (m_char_index == m_char_length + 2 ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length + 2 ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);
            fontRenderer.drawString(ENTER, tft.width() - 15 - fontRenderer.textWidth(ENTER, FONT), y, (m_char_index == m_char_length + 3 ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length + 3 ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);
        }
    }
    else
    {
        const int32_t y_2 = y + fontRenderer.fontHeight(FONT) + 4;
        // align left (SHIFT, SPACE)
        tft.drawRoundRect(15 - 2,   y - 1, fontRenderer.textWidth(SHIFT, FONT) + 4, fontRenderer.fontHeight(FONT) + 2, 3, espgui::TFT_DARKGREY);
        tft.drawRoundRect(15 - 2, y_2 - 1, fontRenderer.textWidth(SPACE, FONT) + 4, fontRenderer.fontHeight(FONT) + 2, 3, espgui::TFT_DARKGREY);

        // align right (BACKSPACE, ENTER); align from tft.width()
        tft.drawRoundRect(tft.width() - 15 - fontRenderer.textWidth(ENTER, FONT) - 2, y - 1, fontRenderer.textWidth(ENTER, FONT) + 4,
                          fontRenderer.fontHeight(FONT) + 2, 3, espgui::TFT_DARKGREY);
        tft.drawRoundRect(tft.width() - 15 - fontRenderer.textWidth(BACKSPACE, FONT) - 2, y_2 - 1, fontRenderer.textWidth(BACKSPACE, FONT) + 4,
                          fontRenderer.fontHeight(FONT) + 2, 3, espgui::TFT_DARKGREY);

        // if (!dont_draw_string)
        {
            // align left (SHIFT, SPACE)
            fontRenderer.drawString(SHIFT, 15, y, (m_char_index == m_char_length ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);
            fontRenderer.drawString(SPACE, 15, y_2, (m_char_index == m_char_length + 1 ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length + 1 ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);

            // align right (BACKSPACE, ENTER); align from tft.width()
            fontRenderer.drawString(BACKSPACE, tft.width() - 15 - fontRenderer.textWidth(BACKSPACE, FONT), y_2, (m_char_index == m_char_length + 2 ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length + 2 ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);
            fontRenderer.drawString(ENTER, tft.width() - 15 - fontRenderer.textWidth(ENTER, FONT), y, (m_char_index == m_char_length + 3 ? espgui::TFT_BLACK : espgui::TFT_WHITE), (m_char_index == m_char_length + 3 ? espgui::TFT_WHITE : espgui::TFT_BLACK), FONT);
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
void Keyboard<TDisplay>::start(TftInterface &tft)
{
    const auto isLandscape = espgui::isLandscape(tft);
    m_keyboard_start_y = isLandscape ? 98 : 120;

    tft.fillRect(1, m_keyboard_start_y - 10, tft.width()-1, tft.height() - m_keyboard_start_y - (isLandscape ? 0 : 30), TFT_BLACK);
    tft.drawSunkenRect(1, m_keyboard_start_y - 10, tft.width()-1, tft.height() - m_keyboard_start_y - (isLandscape ? 0 : 30), TFT_WHITE, TFT_GREY, TFT_BLACK);

    updateCharLength();
    drawKeyboard(tft);

    m_upHeld = std::nullopt;
    m_downHeld = std::nullopt;
}

template<typename TDisplay>
void Keyboard<TDisplay>::redraw(TftInterface &tft)
{
    const auto isLandscape = espgui::isLandscape(tft);

    if (m_needsStart)
    {
        m_needsStart = false;
        tft.fillRect(1, m_keyboard_start_y - 10, tft.width()-1, tft.height() - m_keyboard_start_y - (isLandscape ? 0 : 30), TFT_BLACK);
        tft.drawSunkenRect(1, m_keyboard_start_y - 10, tft.width()-1, tft.height() - m_keyboard_start_y - (isLandscape ? 0 : 30), TFT_WHITE, TFT_GREY, TFT_BLACK);
        updateCharLength();
    }

    if (m_needsRedraw)
    {
        m_needsRedraw = false;
        drawKeyboard(tft);
    }
}

template<typename TDisplay>
void Keyboard<TDisplay>::buttonPressed(Button button)
{
    using namespace std::chrono_literals;

    switch (button)
    {
    case Right:
    {
        m_confirm_pressed_time = espchrono::millis_clock::now();
        break;
    }
    case Left:
        m_back_pressed_time = espchrono::millis_clock::now();
        break;
    case Up:
        moveSelectorLeft();
        m_needsRedraw = true;
        m_upHeld = ButtonHeldInfo { .nextTimestamp = espchrono::millis_clock::now() + 300ms };
        break;
    case Down:
        moveSelectorRight();
        m_needsRedraw = true;
        m_downHeld = ButtonHeldInfo { .nextTimestamp = espchrono::millis_clock::now() + 300ms };
        break;
    default:;
    }
}

template<typename TDisplay>
void Keyboard<TDisplay>::buttonReleased(espgui::Button button)
{
    using namespace std::chrono_literals;

    switch (button)
    {
    case Left:
        if (!m_back_pressed_time)
            return;

        if (espchrono::ago(*m_back_pressed_time) < 350ms)
            m_display.removeLastCharFromShownValue();

        m_back_pressed_time = std::nullopt;
        break;
    case Right:
        if (!m_confirm_pressed_time)
            return;

        if (espchrono::ago(*m_confirm_pressed_time) < 350ms)
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
        }
        m_confirm_pressed_time = std::nullopt;
        break;
    case Up:
        m_upHeld = std::nullopt;
        break;
    case Down:
        m_downHeld = std::nullopt;
        break;
    default:;
    }
}

template<typename TDisplay>
void Keyboard<TDisplay>::update()
{
    using namespace std::chrono_literals;

    const auto now = espchrono::millis_clock::now();
    if (m_back_pressed_time)
    {
        if (espchrono::ago(*m_back_pressed_time) > 350ms)
        {
            m_back_pressed_time = std::nullopt;
            popScreen();
        }
    }

    if (m_confirm_pressed_time)
    {
        if (espchrono::ago(*m_confirm_pressed_time) > 350ms)
        {
            m_confirm_pressed_time = std::nullopt;
            nextScreen();
        }
    }

    if (m_upHeld && now >= m_upHeld->nextTimestamp)
    {
        m_upHeld->nextTimestamp += m_upHeld->counter > 3 ? 100ms : 200ms;
        m_upHeld->counter++;
        moveSelectorLeft();
        m_needsRedraw = true;
    }
    if (m_downHeld && now >= m_downHeld->nextTimestamp)
    {
        m_downHeld->nextTimestamp += m_downHeld->counter > 3 ? 100ms : 200ms;
        m_downHeld->counter++;
        moveSelectorRight();
        m_needsRedraw = true;
    }
}
} // namespace espgui
