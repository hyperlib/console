// <hyper/console/command.cpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <functional>
#include <hyper/console/command.hpp>
#include <hyper/console/option_value.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace hyper {
namespace console {

    Command::Command(): m_options(), m_commands(), m_parent(nullptr) {
    }

    Command::~Command() {
    }

    Command& Command::parent(const Command& command) {
        m_parent = &command;

        return *this;
    }

    Command& Command::name(const std::string& name) {
        m_name = name;

        return *this;
    }

    std::string Command::getName() const {
        return m_name;
    }

    Command& Command::description(const std::string& description) {
        m_description = description;

        return *this;
    }

    std::string Command::getDescription() const {
        return m_description;
    }

    Command& Command::option(Option& option) {
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

    Command& Command::command(Command& cmd) {
        cmd.parent(*this);

        m_commands[cmd.getName()] = &cmd;

        return *this;
    }

    bool Command::hasCommand() const {
        return m_commands.size() > 0;
    }

    Command& Command::handle(const std::function<int(const Command& cmd)> handle_) {
        m_handle = handle_;

        return *this;
    }

    Option* Command::getLongOpt(const std::string& opt) const {
        for (std::size_t n = 0; n < m_options.size(); ++n) {
            if (m_options[n]->getLongOption() == opt) {
                return m_options[n];
            }
        }

        return NULL;
    }


    Option* Command::getShortOpt(const char opt) const {
        for (std::size_t n = 0; n < m_options.size(); ++n) {
            if (m_options[n]->getShortOption() == opt) {
                return m_options[n];
            }
        }

        return NULL;
    }

    Command& Command::parse(int argc, char *argv[]) {
        std::vector<std::string> arguments(argv + 0, argv + argc);

        return parse(arguments);
    }

    Command& Command::parse(std::vector<std::string>& args) {
        m_args.clear();

        args.erase(args.begin());

        /*if (!m_commands.empty() && m_parent) {
            // remove first argument
            args.erase(args.begin());
        }*/

        std::cout << "Parse -------" << std::endl;
        for (auto arg : args) {
            std::cout << "--- arg: " << arg << std::endl;
        }

        m_argv = args;

        for (auto it = args.begin(); it != args.end(); ++it) {
            std::string arg(*it);

            if (arg == "--") {
                ///from here on only non opt args
                for (it++; it != args.end(); ++it) {
                    m_args.push_back(*it);
                }
                break;
            } else if (arg.find("--") == 0) {
                /// long option arg
                std::string opt = arg.substr(2);
                std::string optarg;
                std::size_t equalIdx = opt.find('=');

                if (equalIdx != std::string::npos) {
                    optarg = opt.substr(equalIdx + 1);
                    opt.resize(equalIdx);
                }

                Option* option = NULL;
                if ((option = getLongOpt(opt)) != NULL) {
                    if (option->getType() == OptionValue::None) {
                        if (!optarg.empty()) {
                            option = NULL;
                        }
                    } else if (option->getType() == OptionValue::Required) {
                        if (optarg.empty() && it < args.end()-1) {
                            m_argv.erase(it);
                            optarg = *(it++);
                        }
                    }
                }

                if (option != NULL) {
                    option->parse(opt, optarg.c_str());

                    m_argv.erase(it);
                } else {
                    //@TODO throw error
                    //m_unknown_options.push_back(arg);
                    std::cerr << "Unknown options: " << arg << std::endl;
                }
            } else if (arg.find("-") == 0) {
                std::cout << "--- parse short option: " << arg << std::endl;

                /// short option arg
                std::string opt = arg.substr(1);
                bool unknown = false;

                for (std::size_t m = 0; m < opt.size(); ++m) {
                    char c = opt[m];
                    Option* option = NULL;
                    std::string optarg;
                    std::cout << "--- before getShortOpt (" << c << ")" << std::endl;
                    if ((option = getShortOpt(c)) != NULL) {
                        std::cout << "--- after getShortOpt (" << c << ")" << std::endl;

                        std::cout << "--- option->getType() (" << static_cast<int>(option->getType()) << ")" << std::endl;

                        if (option->getType() == OptionValue::Required) {
                            std::cout << "--- getType == required" << std::endl;
                            /// use the rest of the current argument as optarg
                            optarg = opt.substr(m + 1);
                            /// or the next arg
                            if (optarg.empty() && it < args.end()-1) {
                                m_argv.erase(it);
                                optarg = *(it++);
                            }

                            m = opt.size();
                        } else if (option->getType() == OptionValue::Optional) {
                            std::cout << "--- getType == optional" << std::endl;
                            /// use the rest of the current argument as optarg
                            optarg = opt.substr(m + 1);
                            m = opt.size();
                        }
                        std::cout << "--- end getShortOpt (" << c << ")" << std::endl;
                    }

                    std::cout << "--- option != NULL" << std::endl;
                    if (option != NULL) {
                        option->parse(std::string(1, c), optarg.c_str());
                    } else {
                        unknown = true;
                    }
                }

                if (unknown) {
                    //@TODO throw error
                    std::cerr << "Unknown options: " << arg << std::endl;
                    //m_unknown_options.push_back(arg);
                } else {
                    m_argv.erase(it);
                }
            } else {
                m_args.push_back(arg);
            }
        }

        std::cout << "Parse end -------" << std::endl;

        return *this;
    }

    Command& Command::setOptions(const std::vector<Option*>& options) {
        m_options = options;

        return *this;
    }

    int Command::exec() {
        try {
            // exec handle
            return m_handle(*this);
        } catch (std::bad_function_call& ex) {
            std::cerr << "Bad function call: " << ex.what() << std::endl;

            return EXIT_FAILURE;
        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;

            return EXIT_FAILURE;
        }
    }

    int Command::run() {
        if (m_args.empty() && !m_parent) {
            std::cout << "args empty and root command" << std::endl;

            std::cout << help();

            return EXIT_FAILURE;
        }

        if (m_args.empty() && !m_commands.empty()) {
            std::cout << help();

            return EXIT_FAILURE;
        }

        for (auto arg : m_args) {
            std::cout << "--- arg: " << arg << std::endl;
        }

        std::string command = m_args.front();

        //@TODO: Added external command support with prefix, ex: hyperscale-*
        if (!m_commands.count(command)) {
             std::cout << help();

            return EXIT_FAILURE;
        }

        Command* cmd = m_commands[command];

        if (cmd->hasCommand()) {
            // forward argc/argv to subcommand without this command arg.

            // example: ./hyperscale debug lexer --log-level=debug --foo
            // 1. parse debug lexer --log-level=debug --foo
            // 2. call debug command
            // 3. parse lexer --log-level=debug --foo
            // 4. call lexer
            // 5. parse --log-level=debug --foo
            // 6. exec handle

            cmd->setOptions(m_options);
            cmd->parse(m_argv);

            return cmd->run();
        } else {
            return cmd->exec();
        }
    }

    std::string Command::getNameWithParent() const {
        std::stringstream s;

        if (m_parent != NULL) {
            s << m_parent->getNameWithParent() << " ";
        }

        s << m_name;

        return s.str();
    }

    std::string Command::help() const {
        std::size_t optionRightMargin(20);
        const std::size_t maxDescriptionLeftMargin(40);
    //	const std::size_t descriptionRightMargin(80);

        for (std::size_t opt = 0; opt < m_options.size(); ++opt) {
            optionRightMargin = std::max(optionRightMargin, m_options[opt]->optionToString().size() + 2);
        }

        optionRightMargin = std::min(maxDescriptionLeftMargin - 2, optionRightMargin);

        std::stringstream s;

        s << "Usage:	" << getNameWithParent();

        if (m_commands.empty() && m_options.size() > 0) {
            s << " [OPTIONS]";
        } else if (m_commands.size() > 0) {
            s << " COMMAND";
        }

        s << std::endl;
        s << std::endl;

        if (!m_description.empty()) {
            s << m_description << std::endl;
            s << std::endl;
        }

        if (m_options.size() > 0) {
            s << "Options:" << std::endl;

            for (std::size_t opt = 0; opt < m_options.size(); ++opt) {
                std::string optionStr = m_options[opt]->optionToString();

                if (optionStr.size() < optionRightMargin) {
                    optionStr.resize(optionRightMargin, ' ');
                } else {
                    optionStr += "\n" + std::string(optionRightMargin, ' ');
                }

                s << optionStr;

                std::vector<std::string> lines = m_options[opt]->descriptionToString(20);
                std::string empty(optionRightMargin, ' ');

                for (std::size_t n = 0; n < lines.size(); ++n) {
                    if (n > 0) {
                        s << std::endl << empty;
                    }

                    s << lines[n];
                }

                s << std::endl;
            }
        }

        if (!m_commands.empty()) {
            std::size_t commandRightMargin(14);

            s << "Commands:" << std::endl;

            for (auto& item : m_commands) {
                std::string commandStr = "  " + item.second->getName();

                if (commandStr.size() < commandRightMargin) {
                    commandStr.resize(commandRightMargin, ' ');
                } else {
                    commandStr += "\n" + std::string(commandRightMargin, ' ');
                }

                s << commandStr;

                std::vector<std::string> lines = item.second->descriptionToString(20);
                std::string empty(commandRightMargin, ' ');

                for (std::size_t n = 0; n < lines.size(); ++n) {
                    if (n > 0) {
                        s << std::endl << empty;
                    }

                    s << lines[n];
                }

                s << std::endl;
            }

            s << std::endl;

            s << "Run '" << getNameWithParent() << " COMMAND --help' for more information on a command." << std::endl;
        }

        return s.str();
    }


    std::vector<std::string> Command::descriptionToString(std::size_t width) const {
            std::vector<std::string> lines;
            std::stringstream description(getDescription());
            std::string line;

            while (std::getline(description, line, '\n')) {
                lines.push_back(line);
            }

            return lines;
        }

} // end of console namespace
} // end of hyper namespace
