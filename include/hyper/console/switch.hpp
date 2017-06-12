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

#include <hyper/console/option.hpp>
#include <hyper/console/option_value.hpp>
#include <hyper/console/value.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace hyper {
namespace console {

    class Switch : public Value<bool> {
    public:
        Switch(const std::string& shortOption, const std::string& longOption, const std::string& description):
            Value<bool>(shortOption, longOption, description, false)
        {
            setType(OptionValue::None);
        }

        virtual void parse(const std::string& whatOption, const std::string& value) {
            addValue(true);
        }

        virtual std::string optionToString() const {
            return Option::optionToString();
        }

        Switch& assignTo(bool* var) {
            m_assign_to = var;

            return *this;
        }

        Switch& setDefault(const bool& value) {
            m_default = value;
            m_has_default = true;

            return *this;
        }
    };

} // end of console namespace
} // end of hyper namespace
