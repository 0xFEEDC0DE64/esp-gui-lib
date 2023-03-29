#include "vumeter.h"

// system includes
#include <cmath>
#include <cstring>

// 3rdparty lib includes
#include <cpputils.h>
#include <fontrenderer.h>

// local includes
#include "tftinterface.h"
#include "tftcolors.h"

namespace espgui {
void VuMeter::start(TftInterface &tft)
{
    FontRenderer fontRenderer{tft};

    ltx = 0;
    osx = 120;
    osy = 120;

    // Meter outline
    tft.fillRect(0, 0, 239, 126, TFT_GREY);
    tft.fillRect(5, 3, 230, 119, TFT_WHITE);

    // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
    for (int i = -50; i < 51; i += 5) {
        // Long scale tick length
        int tl = 15;

        // Coodinates of tick to draw
        float sx = cos((i - 90) * 0.0174532925);
        float sy = sin((i - 90) * 0.0174532925);
        uint16_t x0 = sx * (100 + tl) + 120;
        uint16_t y0 = sy * (100 + tl) + 140;
        uint16_t x1 = sx * 100 + 120;
        uint16_t y1 = sy * 100 + 140;

        // Coordinates of next tick for zone fill
        float sx2 = cos((i + 5 - 90) * 0.0174532925);
        float sy2 = sin((i + 5 - 90) * 0.0174532925);
        int x2 = sx2 * (100 + tl) + 120;
        int y2 = sy2 * (100 + tl) + 140;
        int x3 = sx2 * 100 + 120;
        int y3 = sy2 * 100 + 140;

        // Yellow zone limits
        //if (i >= -50 && i < 0) {
        //    tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
        //    tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
        //}

        // Green zone limits
        if (i >= 0 && i < 25) {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
        }

        // Orange zone limits
        if (i >= 25 && i < 50) {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
            tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
        }

        // Short scale tick length
        if (i % 25 != 0) tl = 8;

        // Recalculate coords incase tick lenght changed
        x0 = sx * (100 + tl) + 120;
        y0 = sy * (100 + tl) + 140;
        x1 = sx * 100 + 120;
        y1 = sy * 100 + 140;

        // Draw tick
        tft.drawLine(x0, y0, x1, y1, TFT_BLACK);

        // Check if labels should be drawn, with position tweaks
        if (i % 25 == 0) {
            // Calculate label positions
            x0 = sx * (100 + tl + 10) + 120;
            y0 = sy * (100 + tl + 10) + 140;
            switch (i / 25) {
                case -2: fontRenderer.drawCentreString("0", x0, y0 - 12, TFT_BLACK, TFT_BLACK, 2); break;
                case -1: fontRenderer.drawCentreString("7.5", x0, y0 - 9, TFT_BLACK, TFT_BLACK, 2); break;
                case 0: fontRenderer.drawCentreString("15", x0, y0 - 6, TFT_BLACK, TFT_BLACK, 2); break;
                case 1: fontRenderer.drawCentreString("22.5", x0, y0 - 9, TFT_BLACK, TFT_BLACK, 2); break;
                case 2: fontRenderer.drawCentreString("30", x0, y0 - 12, TFT_BLACK, TFT_BLACK, 2); break;
            }
        }

        // Now draw the arc of the scale
        sx = cos((i + 5 - 90) * 0.0174532925);
        sy = sin((i + 5 - 90) * 0.0174532925);
        x0 = sx * 100 + 120;
        y0 = sy * 100 + 140;
        // Draw scale arc, don't draw the last part
        if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
    }

    fontRenderer.drawString("KM/h", 5 + 230 - 40, 119 - 20, TFT_BLACK, TFT_BLACK, 2); // Units at bottom right
    fontRenderer.drawCentreString("KM/h", 120, 70, TFT_BLACK, TFT_BLACK, 4); // Comment out to avoid font 4
    tft.drawRect(5, 3, 230, 119, TFT_BLACK); // Draw bezel line
}

namespace {
char * dtostrf(double number, signed char width, unsigned char prec, char *s) {
    bool negative = false;

    if (std::isnan(number)) {
        std::strcpy(s, "nan");
        return s;
    }
    if (std::isinf(number)) {
        std::strcpy(s, "inf");
        return s;
    }

    char* out = s;

    int fillme = width; // how many cells to fill for the integer part
    if (prec > 0) {
        fillme -= (prec+1);
    }

    // Handle negative numbers
    if (number < 0.0) {
        negative = true;
        fillme--;
        number = -number;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    // I optimized out most of the divisions
    double rounding = 2.0;
    for (uint8_t i = 0; i < prec; ++i)
        rounding *= 10.0;
    rounding = 1.0 / rounding;

    number += rounding;

    // Figure out how big our number really is
    double tenpow = 1.0;
    int digitcount = 1;
    while (number >= 10.0 * tenpow) {
        tenpow *= 10.0;
        digitcount++;
    }

    number /= tenpow;
    fillme -= digitcount;

    // Pad unused cells with spaces
    while (fillme-- > 0) {
        *out++ = ' ';
    }

    // Handle negative sign
    if (negative) *out++ = '-';

    // Print the digits, and if necessary, the decimal point
    digitcount += prec;
    int8_t digit = 0;
    while (digitcount-- > 0) {
        digit = (int8_t)number;
        if (digit > 9) digit = 9; // insurance
        *out++ = (char)('0' | digit);
        if ((digitcount == prec) && (prec > 0)) {
            *out++ = '.';
        }
        number -= digit;
        number *= 10.0;
    }

    // make sure the string is terminated
    *out = 0;
    return s;
}
}

void VuMeter::redraw(TftInterface &tft, float value)
{
    FontRenderer fontRenderer{tft};

    char buf[8]; dtostrf(value, 4, 0, buf);
    fontRenderer.drawRightString(buf, 50, 119 - 25, TFT_BLACK, TFT_WHITE, 4);

    if (value < -3) value = -3; // Limit value to emulate needle end stops
    if (value > 33) value = 33;

    float sdeg = cpputils::mapValue<float>(value, -3, 33, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    fontRenderer.drawCentreString("KM/h", 120, 70, TFT_BLACK, TFT_BLACK, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = sx * 98 + 120;
    osy = sy * 98 + 140;

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_RED);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_MAGENTA);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_RED);
}
} // namespace espgui
