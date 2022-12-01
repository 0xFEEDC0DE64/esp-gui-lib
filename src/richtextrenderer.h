#pragma once

// system includes
#include <string_view>
#include <string>

// forward declares
namespace espgui { class TftInterface; }

namespace espgui {

void richTextEscape(std::string &subject);
std::string richTextEscape(std::string_view subject);

int16_t renderRichText(TftInterface &tft, std::string_view str, int32_t poX, int32_t poY, uint16_t color, uint16_t bgcolor, uint8_t font);

} // namespace espgui
