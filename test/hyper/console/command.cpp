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

BOOST_AUTO_TEST_SUITE(hyper_console_command)

BOOST_AUTO_TEST_CASE(test_command_simple) {
    std::vector<std::string> args = {"test-cmd", "-l=info", "version"};

    hyper::console::Application* app = new hyper::console::Application();
    app->name("test-cmd");
    app->description("test command");
    app->command(hyper::console::Command()
        .name("version")
        .description("Show the test-cmd version information")
        .handle([](const hyper::console::Command& cmd_) {
            return EXIT_SUCCESS;
        })
    );

    app->parse(args);

    BOOST_CHECK_EQUAL(app->run(), EXIT_SUCCESS);

    delete app;
}

BOOST_AUTO_TEST_CASE(test_command_with_sub_command) {
    std::vector<std::string> args = {"test-cmd", "package", "search", "my-package"};

    hyper::console::Application* app = new hyper::console::Application();
    app->name("test-cmd");
    app->description("test command");
    app->command(hyper::console::Command()
        .name("package")
        .description("package manager command")
        .command(hyper::console::Command()
            .name("search")
            .description("Search package")
            .handle([](const hyper::console::Command& cmd_) {
                return EXIT_SUCCESS;
            })
        )
    );

    app->parse(args);

    BOOST_CHECK_EQUAL(app->run(), EXIT_SUCCESS);

    delete app;
}

BOOST_AUTO_TEST_SUITE_END()
