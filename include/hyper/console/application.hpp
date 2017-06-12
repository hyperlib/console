// <hyper/console/application.hpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#pragma once

#include <hyper/console/command.hpp>
#include <hyper/console/implicit.hpp>
#include <hyper/console/switch.hpp>

namespace hyper {
namespace console {

    class Application: public Command {
    public:
        Application(): Command() {
            Switch helpOption("h", "help", "Print usage");
            Implicit<std::string> logLevelOption(
                "l",
                "log-level",
                "Set the logging level (\"debug\", \"info\", \"warn\", \"error\", \"fatal\")",
                "info"
            );

            option(helpOption);
            option(logLevelOption);
        }
    };

} // end of console namespace
} // end of hyper namespace
