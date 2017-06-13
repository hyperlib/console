// <hyper/console/command.cpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#include <boost/test/unit_test.hpp>
#include <hyper/console/application.hpp>

class VersionCommand: public hyper::console::Command {
public:
    void configuration() {
        setName("version");
        setDescription("Show the test-cmd version information");
    }

    int execute() {
        return EXIT_SUCCESS;
    }
};


class PackageSearchCommand: public hyper::console::Command {
public:
    void configuration() {
        setName("search");
        setDescription("Search package");
    }

    int execute() {
        auto args = getArguments();
        
        BOOST_REQUIRE_EQUAL(args.size(), 1ull);
        
        std::string package = args.front();

        BOOST_CHECK_EQUAL(package, "my-package");

        return EXIT_SUCCESS;
    }
};

class PackageCommand: public hyper::console::Command {
public:
    void configuration() {
        setName("package");
        setDescription("package manager command");
        addCommand(new PackageSearchCommand());
    }
};

BOOST_AUTO_TEST_SUITE(hyper_console_command)

BOOST_AUTO_TEST_CASE(test_command_simple) {
    std::vector<std::string> args = {"test-cmd", "-l=info", "version"};

    hyper::console::Application* app = new hyper::console::Application();

    app->setName("test-cmd");
    app->setDescription("test command");
    app->addCommand(new VersionCommand());

    app->parse(args);

    BOOST_CHECK_EQUAL(app->run(), EXIT_SUCCESS);

    delete app;
}

BOOST_AUTO_TEST_CASE(test_command_with_sub_command) {
    std::vector<std::string> args = {"test-cmd", "package", "search", "my-package"};

    hyper::console::Application* app = new hyper::console::Application();

    app->setName("test-cmd");
    app->setDescription("test command");
    app->addCommand(new PackageCommand());

    app->parse(args);

    BOOST_CHECK_EQUAL(app->run(), EXIT_SUCCESS);

    delete app;
}

BOOST_AUTO_TEST_SUITE_END()
