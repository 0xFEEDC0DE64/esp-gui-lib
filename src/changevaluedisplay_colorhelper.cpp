#include "changevaluedisplay_colorhelper.h"

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <tftutils.h>

// local includes
#include "tftcolors.h"

namespace espgui {
namespace {
constexpr const auto INNER_CIRCLE_RADIUS = 10;
} // namespace

void ChangeValueDisplay<cpputils::ColorHelper>::start()
{
    Base::start();

    m_value = this->getValue();
}

void ChangeValueDisplay<cpputils::ColorHelper>::initScreen(TftInterface &tft)
{
    Base::initScreen(tft);

    const int16_t center_x = tft.width() / 2;
    const int16_t center_y = (tft.height()+36) / 2; // 36 is the height of the title bar

    ESP_LOGI("ChangeValueDisplay<cpputils::ColorHelper>::initScreen", "center_x: %d, center_y: %d, color: %s", center_x, center_y, toString(m_value).c_str());

    drawHSVWheel(tft, center_x, center_y, center_y + INNER_CIRCLE_RADIUS*2);

    tft.fillCircle(center_x, center_y, INNER_CIRCLE_RADIUS, colorToNumber(m_value));
}

void ChangeValueDisplay<cpputils::ColorHelper>::redraw(TftInterface &tft)
{
    Base::redraw(tft);
}

void ChangeValueDisplay<cpputils::ColorHelper>::buttonPressed(Button button)
{
    //Base::buttonPressed(button);
    switch (button)
    {
    case Button::Left:
        back();
        break;
    default:;
    }
}

void ChangeValueDisplay<cpputils::ColorHelper>::buttonReleased(Button button)
{
    //Base::buttonReleased(button);
}

void ChangeValueDisplay<cpputils::ColorHelper>::confirmValue()
{

}

void ChangeValueDisplay<cpputils::ColorHelper>::drawHSVWheel(TftInterface &tft, int16_t x, int16_t y, uint8_t d) const
{
    // use tft.fillCircleHelper() to draw the wheel
    constexpr const auto circle_count = 4;
    constexpr const auto section_count = 8;
    const auto min_radius = INNER_CIRCLE_RADIUS;
    const auto max_radius = d / 2;

    for (uint8_t i = 0; i < circle_count; i++)
    {
        tft.drawCircle(x, y, min_radius + i * (max_radius - min_radius) / circle_count, TFT_WHITE);
    }

    auto hsv = cpputils::HsvColor{0, 255, 255};

    // use fillArc(TftInterface &tft, int x, int y, int start_angle, int rx, int ry, int w, unsigned int color)

    for (uint8_t i = 0; i < section_count; i++)
    {
        const auto color = cpputils::colorToNumber(cpputils::HsvToRgb(hsv));
        const auto start_angle = i * 360 / section_count;
        const auto end_angle = (i + 1) * 360 / section_count;

        hsv.h += 255 / section_count % 255;
    }
}
} // namespace espgui
