// <hyper/_console/command.hpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#pragma once

#include <boost/program_options.hpp>

namespace hyper::console {
    namespace po = boost::program_options;

    typedef int (*Command)(po::variables_map &vm, po::parsed_options &options, po::options_description &desc);
}
