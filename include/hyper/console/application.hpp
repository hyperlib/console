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
            addOption(new Switch("h", "help", "Print usage"));
            addOption(new Implicit<std::string>(
                "l",
                "log-level",
                "Set the logging level (\"debug\", \"info\", \"warn\", \"error\", \"fatal\")",
                "info"
            ));
        }
        
        virtual ~Application() {
            
        }
    };

} // end of console namespace
} // end of hyper namespace
