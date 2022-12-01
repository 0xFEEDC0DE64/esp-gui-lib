#pragma once

// 3rdparty lib includes
#include "TFT_eSPI.h"

// local includes
#include "tftinterface.h"

namespace espgui {

class TftESpiImpl : public TftInterface
{
public:
    void init() { m_tft.init(); }

    void     drawPixel(int32_t x, int32_t y, uint16_t color) override { m_tft.drawPixel(x, y, color); }
    void     drawChar(int32_t x, int32_t y, uint16_t c, uint16_t color, uint16_t bg, uint8_t size) override { m_tft.drawChar(x, y, c, color, bg, size); }
    void     drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint16_t color) override { m_tft.drawLine(xs, ys, xe, ye, color); }
    void     drawFastVLine(int32_t x, int32_t y, int32_t h, uint16_t color) override { m_tft.drawFastVLine(x, y, h, color); }
    void     drawFastHLine(int32_t x, int32_t y, int32_t w, uint16_t color) override { m_tft.drawFastHLine(x, y, w, color); }
    void     fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t color) override { m_tft.fillRect(x, y, w, h, color); }

    int16_t  drawChar(uint16_t uniCode, int32_t x, int32_t y, uint16_t color, uint16_t bgcolor, uint8_t font) override { return m_tft.drawChar(uniCode, x, y, color, bgcolor, font); }
    int16_t  height() const override { return m_tft.height(); }
    int16_t  width() const override { return m_tft.width(); }

    void     setRotation(uint8_t r) override { m_tft.setRotation(r); }
    uint8_t  getRotation(void) const { return m_tft.getRotation(); }

    // Graphics drawing
    void     fillScreen(uint32_t color) override { m_tft.fillScreen(color); }
    void     drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) override { m_tft.drawRect(x, y, w, h, color); }
    void     drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color) override { m_tft.drawRoundRect(x, y, w, h, radius, color); }
    void     fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color) override { m_tft.fillRoundRect(x, y, w, h, radius, color); }

    void     fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2) override { m_tft.fillRectVGradient(x, y, w, h, color1, color2); }
    void     fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2) override { m_tft.fillRectHGradient(x, y, w, h, color1, color2); }

    uint16_t drawPixel(int32_t x, int32_t y, uint32_t color, uint8_t alpha, uint32_t bg_color = 0x00FFFFFF) override { return m_tft.drawPixel(x, y, color, alpha, bg_color); }

    void     drawSpot(float ax, float ay, float r, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF) override { m_tft.drawSpot(ax, ay, r, fg_color, bg_color); }

    void     fillSmoothCircle(int32_t x, int32_t y, int32_t r, uint32_t color, uint32_t bg_color = 0x00FFFFFF) override { m_tft.fillSmoothCircle(x, y, r, color, bg_color); }

    void     fillSmoothRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color, uint32_t bg_color = 0x00FFFFFF) override { m_tft.fillSmoothRoundRect(x, y, w, h, radius, color, bg_color); }

    void     drawWideLine(float ax, float ay, float bx, float by, float wd, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF) override { m_tft.drawWideLine(ax, ay, bx, by, wd, fg_color, bg_color); }

    void     drawWedgeLine(float ax, float ay, float bx, float by, float aw, float bw, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF) override { m_tft.drawWedgeLine(ax, ay, bx, by, aw, bw, fg_color, bg_color); }

    void     drawSunkenRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color0, uint32_t color1, uint32_t color2) override { m_tft.drawSunkenRect(x, y, w, h, color0, color1, color2); }

    void     drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color) override { m_tft.drawCircle(x, y, r, color); }
    void     drawCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, uint32_t color) override { m_tft.drawCircleHelper(x, y, r, cornername, color); }
    void     fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color) override { m_tft.fillCircle(x, y, r, color); }
    void     fillCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color) override { m_tft.fillCircleHelper(x, y, r, cornername, delta, color); }

    void     drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color) override { m_tft.drawEllipse(x, y, rx, ry, color); }
    void     fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color) override { m_tft.fillEllipse(x, y, rx, ry, color); }

    void     drawTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color) override { m_tft.drawTriangle(x1, y1, x2, y2, x3, y3, color); }
    void     fillTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color) override { m_tft.fillTriangle(x1, y1, x2, y2, x3, y3, color); }

    int16_t  textWidth(std::string_view string, uint8_t font) override { return m_tft.textWidth(string, font); }
    int16_t  fontHeight(int16_t font) override { return m_tft.fontHeight(font); }

    int16_t drawString(std::string_view string, int32_t x, int32_t y, uint16_t color, uint16_t bgcolor, uint8_t font) override { return m_tft.drawString(string, x, y, color, bgcolor, font); }
    int16_t drawCentreString(std::string_view string, int32_t x, int32_t y, uint16_t color, uint16_t bgcolor, uint8_t font) override { return m_tft.drawCentreString(string, x, y, color, bgcolor, font); }
    int16_t drawRightString(std::string_view string, int32_t x, int32_t y, uint16_t color, uint16_t bgcolor, uint8_t font) override { return m_tft.drawRightString(string, x, y, color, bgcolor, font); }

    void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data) { m_tft.pushImage(x, y, w, h, data); }
    void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data, uint16_t transparent) { m_tft.pushImage(x, y, w, h, data, transparent); }

private:
    TFT_eSPI m_tft;
};

} // namespace espgui
