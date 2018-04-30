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

#include <exception>
#include <functional>
#include <hyper/console/option.hpp>
#include <hyper/console/value.hpp>
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

        virtual ~Command();

        Command& setParent(const Command* command);

        Command& setName(const std::string& name);

        std::string getName() const;

        Command& setDescription(const std::string& description);

        std::string getDescription() const;

        Command& addOption(Option* option);

        Command& addCommand(Command* command);

        bool hasCommand() const;

        template<typename T>
        Value<T>* getLongOpt(const std::string& opt) const {
            return static_cast<Value<T>*>(getLongOpt(opt));
        }

        Option* getLongOpt(const std::string& opt) const;

        template<typename T>
        Value<T>* getShortOpt(const char opt) const {
            return static_cast<Value<T>*>(getShortOpt(opt));
        }

        Option* getShortOpt(const char opt) const;

        std::vector<std::string>& getArguments();

        Command& parse(int argc, char *argv[]);

        Command& parse(std::vector<std::string>& args);

        Command& setOptions(const std::vector<Option*>& options);

        int run();

        int exec();

        std::string getNameWithParent() const;

        std::string help() const;

        std::vector<std::string> descriptionToString(std::size_t width = 40) const;

        virtual void configuration() {}

        virtual int execute() {
            throw std::runtime_error("Implement execute() for command");

            return EXIT_FAILURE;
        }
    };

} // end of console namespace
} // end of hyper namespace
