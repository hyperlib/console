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
#include <hyper/console>

BOOST_AUTO_TEST_SUITE(hyper_console_command)

BOOST_AUTO_TEST_CASE(test_command) {
    std::vector<std::string> args = {"test-cmd", "-l=info", "version"};

    hyper::console::Application* app = new hyper::console::Application();
    app->name("test-cmd");
    app->description("test command");
    app->command([](){
        auto cmd = std::make_shared<hyper::console::Command>();

        cmd->name("version");
        cmd->description("Show the hyperscale version information");
        cmd->handle([](const hyper::console::Command& cmd_) {
            return EXIT_SUCCESS;
        });

        return cmd;
    }());

    app->parse(args);

    BOOST_CHECK_EQUAL(app->run(), EXIT_SUCCESS);

    delete app;
}

BOOST_AUTO_TEST_SUITE_END()
