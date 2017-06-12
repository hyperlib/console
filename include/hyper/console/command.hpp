// <hyper/console/command.hpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#pragma once

#include <functional>
#include <hyper/console/option.hpp>
#include <hyper/console/option_value.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace hyper {
namespace console {

    class Command;

    class Command {
    protected:
        std::string m_name;

        std::string m_description;

        std::vector<Option*> m_options;

        std::map<std::string, Command*> m_commands;

        std::vector<std::string> m_args;

        const Command* m_parent;

        std::function<int(const Command& cmd)> m_handle;

        std::vector<std::string> m_argv;

    public:
        Command();

        ~Command();

        Command& parent(const Command& command);

        Command& name(const std::string& name);

        std::string getName() const;

        Command& description(const std::string& description);

        std::string getDescription() const;

        //Command& option(Option& option);

        template<typename T>
        Command& option(T& option) {
            for (std::size_t n = 0; n < m_options.size(); ++n) {
                if ((option.getShortOption() != 0) && (option.getShortOption() == m_options[n]->getShortOption())) {
                    throw std::invalid_argument("dublicate short option '-" + std::string(1, option.getShortOption()) + "'");
                }

                if (!option.getLongOption().empty() && (option.getLongOption() == (m_options[n]->getLongOption()))) {
                    throw std::invalid_argument("dublicate long option '--" + option.getLongOption() + "'");
                }
            }

            m_options.push_back(&option);

            return *this;
        }

        Command& command(Command& command);

        bool hasCommand() const;

        Command& handle(const std::function<int(const Command& cmd_)> handle_);

        Option* getLongOpt(const std::string& opt) const;

        Option* getShortOpt(const char opt) const;

        Command& parse(int argc, char *argv[]);

        Command& parse(std::vector<std::string>& args);

        Command& setOptions(const std::vector<Option*>& options);

        int run();

        int exec();

        std::string getNameWithParent() const;

        std::string help() const;

        std::vector<std::string> descriptionToString(std::size_t width = 40) const;
    };

} // end of console namespace
} // end of hyper namespace
