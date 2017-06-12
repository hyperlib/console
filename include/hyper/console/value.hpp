// <hyper/console/value.hpp> -*- C++ -*-

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
#include <sstream>
#include <string>
#include <vector>

namespace hyper {
namespace console {

    template<class T>
    class Value : public Option {
    public:
        Value(const std::string& shortOption, const std::string& longOption, const std::string& description):
            Option(OptionValue::Required, shortOption, longOption, description),
            m_assign_to(NULL),
            m_has_default(false)
        {
        }

        Value(const std::string& shortOption, const std::string& longOption, const std::string& description, const T& defaultVal):
            Option(OptionValue::Required, shortOption, longOption, description),
            m_assign_to(NULL),
            m_default(defaultVal),
            m_has_default(true)
        {
        }

        Value<T>& assignTo(T* var) {
            m_assign_to = var;

            return *this;
        }

        Value<T>& setDefault(const T& value) {
            m_default = value;
            m_has_default = true;

            return *this;
        }

        T getValue(std::size_t idx = 0) const {
            if (!isSet()) {
                if (m_has_default) {
                    return m_default;
                } else {
                    std::stringstream optionStr;

                    if (getShortOption() != 0) {
                        optionStr << "-" << getShortOption();
                    } else {
                        optionStr << "--" << getLongOption();
                    }

                    throw std::out_of_range("option not set: \"" + optionStr.str() + "\"");
                }
            }

            if (idx >= m_count) {
                std::stringstream optionStr;
                optionStr << "index out of range (" << idx << ") for \"";

                if (getShortOption() != 0) {
                    optionStr << "-" << getShortOption();
                } else {
                    optionStr << "--" << getLongOption();
                }

                optionStr << "\"";

                throw std::out_of_range(optionStr.str());
            }

            return m_values[idx];
        }

        virtual void parse(const std::string& whatOption, const std::string& value) {
            T parsedValue;
            std::string strValue;

            if (!value.empty()) {
                strValue = value;
            }

            std::istringstream is(strValue);
            int valuesRead = 0;

            while (is.good()) {
                if (is.peek() != EOF) {
                    is >> parsedValue;
                } else {
                    break;
                }

                valuesRead++;
            }

            if (is.fail()) {
                throw std::invalid_argument("invalid argument for " + whatOption + ": '" + strValue + "'");
            }

            if (valuesRead > 1) {
                throw std::invalid_argument("too many arguments for " + whatOption + ": '" + strValue + "'");
            }

            if (strValue.empty()) {
                throw std::invalid_argument("missing argument for " + whatOption);
            }

            addValue(parsedValue);
        }

        std::string optionToString() const {
            std::stringstream ss;
            ss << Option::optionToString() << " arg";

            if (m_has_default) {
                std::stringstream defaultStr;
                defaultStr << m_default;
                if (!defaultStr.str().empty()) {
                    ss << " (=" << m_default << ")";
                }
            }

            return ss.str();
        }

    protected:

        virtual void addValue(const T& value) {
            m_values.push_back(value);
            ++m_count;

            updateReference();
        }

        virtual void updateReference() {
            if (m_assign_to != NULL) {
                if (isSet() || m_has_default) {
                    *m_assign_to = getValue();
                }
            }
        }

        T* m_assign_to;
        std::vector<T> m_values;
        T m_default;
        bool m_has_default;
    };

    /*template<>
    void Value<std::string>::parse(const std::string& whatOption, const std::string& value) {
        if (value.empty()) {
            throw std::invalid_argument("missing argument for " + whatOption);
        }

        std::cout << "----- Value<std::string>::Parse -------" << std::endl;

        std::cout << "----- Start Value::AddValue -------: " << value << std::endl;
        addValue(value);
        std::cout << "----- End Value::AddValue -------: " << value << std::endl;
    }*/

} // end of console namespace
} // end of hyper namespace
