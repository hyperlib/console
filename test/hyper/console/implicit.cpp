// <hyper/console/implicit.cpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#include <boost/test/unit_test.hpp>
#include <hyper/console/implicit.hpp>

BOOST_AUTO_TEST_SUITE(hyper_console_implicit)

BOOST_AUTO_TEST_CASE(test_implicit_with_value) {
    hyper::console::Implicit<std::string> option("l", "log-level", "Log level", "info");

    BOOST_CHECK_EQUAL(option.getValue(), "info");

    option.parse("l", "debug");

    BOOST_CHECK_EQUAL(option.getValue(), "debug");
}

BOOST_AUTO_TEST_CASE(test_implicit_assign_to) {
    hyper::console::Implicit<std::string> option("l", "log-level", "Log level", "info");

    std::string actual = "";

    option.assignTo(&actual);

    option.parse("l", "error");

    BOOST_CHECK_EQUAL(actual, "error");
}

BOOST_AUTO_TEST_SUITE_END()
