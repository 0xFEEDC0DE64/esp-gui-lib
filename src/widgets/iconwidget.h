#pragma once

// esp-idf includes
#include <esp_log.h>

// local includes
#include "icon.h"
#include "tftcolors.h"
#include "tftinterface.h"

namespace espgui {

class IconWidget
{
    static constexpr const char * const TAG = "IconWidget";
public:
    IconWidget(int x, int y, int iconWidth, int iconHeight, uint16_t bgcolor = espgui::TFT_BLACK);

    void start(TftInterface &tft);

    void start(TftInterface &tft, int32_t iconWidth, int32_t iconHeight, const uint16_t *icon);

    void redraw(TftInterface &tft, int32_t iconWidth, int32_t iconHeight, const uint16_t *icon, uint16_t bgcolor, bool forceRedraw = false);

    void redraw(TftInterface &tft, int32_t iconWidth, int32_t iconHeight, const uint16_t *icon, bool forceRedraw = false);

    void clear(espgui::TftInterface &tft, uint16_t bgcolor);

    void clear(espgui::TftInterface &tft);

    int x() const { return m_x; }

    int y() const { return m_y; }

private:
    const int m_x;
    const int m_y;
    const int m_iconWidth;
    const int m_iconHeight;

    uint16_t m_bgcolor;

    const uint16_t *m_lastIcon;
};

} // namespace espgui
