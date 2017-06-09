// <hyper/_console/application.hpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#pragma once

#include <hyper/_console/command.hpp>
#include <hyper/_console/implicit.hpp>
#include <hyper/_console/switch.hpp>
#include <memory>

namespace hyper {
namespace console {

    class Application: public Command {
    public:
        Application(): Command() {
            option(std::make_shared<Switch>("h", "help", "Print usage"));
            option(std::shared_ptr<Implicit<std::string>>(new Implicit<std::string>(
                "l",
                "log-level",
                "Set the logging level (\"debug\", \"info\", \"warn\", \"error\", \"fatal\")",
                "info"
            )));
        }
    };

} // end of console namespace
} // end of hyper namespace
