#pragma once

// system includes
#include <string_view>
#include <string>

// local includes
#include "tftinstance.h"

namespace espgui {

void richTextEscape(std::string &subject);
std::string richTextEscape(std::string_view subject);

int16_t renderRichText(std::string_view str, int32_t poX, int32_t poY);
int16_t renderRichText(std::string_view str, int32_t poX, int32_t poY, uint8_t font);

} // namespace espgui
