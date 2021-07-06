// <hyper/console/switch.cpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#include <boost/test/unit_test.hpp>
#include "hyper/console/switch.hpp"

BOOST_AUTO_TEST_SUITE(hyper_console_switch)

BOOST_AUTO_TEST_CASE(test_switch) {
    hyper::console::Switch option("h", "help", "Print Usage");

    BOOST_CHECK_EQUAL(option.getValue(), false);

    option.parse("h", "");

    BOOST_CHECK_EQUAL(option.getValue(), true);

    bool actual = false;

    option.assignTo(&actual);

    option.parse("h", "");

    BOOST_CHECK_EQUAL(actual, true);
}

BOOST_AUTO_TEST_SUITE_END()
