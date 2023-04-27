#include "richtexthelper.h"

// 3rdparty lib includes
#include <strutils.h>

namespace espgui {

void richTextEscape(std::string &subject)
{
    cpputils::stringReplaceAll('&', "&&", subject);
}

std::string richTextEscape(std::string_view subject)
{
    return cpputils::stringReplaceAll('&', "&&", subject);
}

} // namespace espgui
