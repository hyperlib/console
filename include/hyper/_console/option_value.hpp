// <hyper/_console/option_value.hpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#pragma once

namespace hyper {
namespace console {

    enum class OptionValue {
        None = 0,  // option never takes an argument
        Required,  // option always requires an argument
        Optional   // option may take an argument
    };

} // end of console namespace
} // end of hyper namespace
