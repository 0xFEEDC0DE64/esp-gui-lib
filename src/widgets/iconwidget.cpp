#include "iconwidget.h"

namespace espgui {
void IconWidget::start(TftInterface &tft)
{
    m_lastIcon = nullptr;
}

void IconWidget::start(TftInterface &tft, const int32_t iconWidth, const int32_t iconHeight, const uint16_t *icon)
{
    if (m_iconWidth != iconWidth || m_iconHeight != iconHeight)
    {
        ESP_LOGE(TAG, "Icon size mismatch: %dx%d vs %ldx%ld", m_iconWidth, m_iconHeight, iconWidth, iconHeight);
        return;
    }

    m_lastIcon = icon;

    if (icon)
        tft.pushImage(m_x, m_y, m_iconWidth, m_iconHeight, icon);
}

void IconWidget::redraw(TftInterface &tft, const int32_t iconWidth, const int32_t iconHeight, const uint16_t *icon, uint16_t bgcolor, bool forceRedraw)
{
    if (m_iconWidth != iconWidth || m_iconHeight != iconHeight)
    {
        ESP_LOGE(TAG, "Icon size mismatch: %dx%d vs %ldx%ld", m_iconWidth, m_iconHeight, iconWidth, iconHeight);
        return;
    }

    if (forceRedraw || m_lastIcon != icon)
    {
        if (icon)
            tft.pushImage(m_x, m_y, m_iconWidth, m_iconHeight, icon);
        else if (m_lastIcon)
            tft.fillRect(m_x, m_y, m_iconWidth, m_iconHeight, bgcolor);

        m_lastIcon = icon;
    }
}

void IconWidget::redraw(TftInterface &tft, const int32_t iconWidth, const int32_t iconHeight, const uint16_t *icon, bool forceRedraw)
{
    redraw(tft, iconWidth, iconHeight, icon, m_bgcolor, forceRedraw);
}

void IconWidget::clear(TftInterface &tft, uint16_t bgcolor)
{
    if (m_lastIcon)
        tft.fillRect(m_x, m_y, m_iconWidth, m_iconHeight, bgcolor);

    m_lastIcon = nullptr;
}

void IconWidget::clear(TftInterface &tft)
{
    clear(tft, m_bgcolor);
}

IconWidget::IconWidget(int x, int y, int iconWidth, int iconHeight, uint16_t bgcolor):
        m_x{x},
        m_y{y},
        m_iconWidth{iconWidth},
        m_iconHeight{iconHeight},
        m_bgcolor{bgcolor},
        m_lastIcon{nullptr}
{}
} // namespace espgui
