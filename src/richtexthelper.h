#pragma once

namespace espgui {
namespace colors {
constexpr char RED[] = "&1";    // #ff0000 (TFT_RED)
constexpr char GREEN[] = "&2";  // #00ff00 (TFT_GREEN)
constexpr char BLUE[] = "&3";   // #0000ff (TFT_BLUE)
constexpr char YELLOW[] = "&4"; // #ffff00 (TFT_YELLOW)
constexpr char BLACK[] = "&5";  // #000000 (TFT_BLACK)
constexpr char WHITE[] = "&6";  // #ffffff (TFT_WHITE)
constexpr char GREY[] = "&7";   // #888888 (TFT_GREY)
constexpr char RESET[] = "&0";  // reset to previous color set by tft.setTextColor()
} // namespace colors

namespace fonts {
constexpr char SMALL[] = "&s";  // tft.setTextFont(2)
constexpr char MEDIUM[] = "&m"; // tft.setTextFont(4)
constexpr char RESTORE[] = "&f";  // restore original font
} // namespace fonts
} // namespace espgui
