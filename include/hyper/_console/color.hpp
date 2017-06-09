// <hyper/_console/color.hpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#pragma once

#include <string>

namespace hyper {
namespace console {
namespace color {
    static const std::string ResetAll = "\033[0m";

    static const std::string Bold       = "\033[1m";
    static const std::string Dim        = "\033[2m";
    static const std::string Underlined = "\033[4m";
    static const std::string Blink      = "\033[5m";
    static const std::string Reverse    = "\033[7m";
    static const std::string Hidden     = "\033[8m";

    static const std::string ResetBold       = "\033[21m";
    static const std::string ResetDim        = "\033[22m";
    static const std::string ResetUnderlined = "\033[24m";
    static const std::string ResetBlink      = "\033[25m";
    static const std::string ResetReverse    = "\033[27m";
    static const std::string ResetHidden     = "\033[28m";

    static const std::string Default      = "\033[39m";
    static const std::string Black        = "\033[30m";
    static const std::string Red          = "\033[31m";
    static const std::string Green        = "\033[32m";
    static const std::string Yellow       = "\033[33m";
    static const std::string Blue         = "\033[34m";
    static const std::string Magenta      = "\033[35m";
    static const std::string Cyan         = "\033[36m";
    static const std::string LightGray    = "\033[37m";
    static const std::string DarkGray     = "\033[90m";
    static const std::string LightRed     = "\033[91m";
    static const std::string LightGreen   = "\033[92m";
    static const std::string LightYellow  = "\033[93m";
    static const std::string LightBlue    = "\033[94m";
    static const std::string LightMagenta = "\033[95m";
    static const std::string LightCyan    = "\033[96m";
    static const std::string White        = "\033[97m";

    static const std::string BackgroundDefault      = "\033[49m";
    static const std::string BackgroundBlack        = "\033[40m";
    static const std::string BackgroundRed          = "\033[41m";
    static const std::string BackgroundGreen        = "\033[42m";
    static const std::string BackgroundYellow       = "\033[43m";
    static const std::string BackgroundBlue         = "\033[44m";
    static const std::string BackgroundMagenta      = "\033[45m";
    static const std::string BackgroundCyan         = "\033[46m";
    static const std::string BackgroundLightGray    = "\033[47m";
    static const std::string BackgroundDarkGray     = "\033[100m";
    static const std::string BackgroundLightRed     = "\033[101m";
    static const std::string BackgroundLightGreen   = "\033[102m";
    static const std::string BackgroundLightYellow  = "\033[103m";
    static const std::string BackgroundLightBlue    = "\033[104m";
    static const std::string BackgroundLightMagenta = "\033[105m";
    static const std::string BackgroundLightCyan    = "\033[106m";
    static const std::string BackgroundWhite        = "\033[107m";

} // end of color namespace
} // end of console namespace
} // end of hyper namespace
