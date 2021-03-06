// "implicit.hpp> -*- C++ -*-

/**
 * Hyper
 *
 * (c) 2017 Axel Etcheverry
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "option.hpp"
#include "option_value.hpp"
#include "value.hpp"

namespace hyper {
namespace console {

    template<class T>
    class Implicit : public Value<T> {
    public:
        Implicit(const std::string& shortOption, const std::string& longOption, const std::string& description, const T& implicitVal):
            Value<T>(shortOption, longOption, description, implicitVal)
        {
            Value<T>::setType(OptionValue::Optional);
        }

        Implicit(const std::string& shortOption, const std::string& longOption, const std::string& description, const T& implicitVal, T* assignTo):
            Value<T>(shortOption, longOption, description, implicitVal, assignTo)
        {
            Value<T>::setType(OptionValue::Optional);
        }

        Implicit<T>& assignTo(T* var) {
            Value<T>::assignTo(var);

            return *this;
        }

        virtual void parse(const std::string& whatOption, const std::string& value) {
            if (!value.empty()) {
                Value<T>::parse(whatOption, value);
            } else {
                this->addValue(this->m_default);
            }
        }

        virtual std::string optionToString() const {
            std::stringstream ss;
            ss << Option::optionToString() << " [=arg(=" << this->m_default << ")]";

            return ss.str();
        }


        Implicit<T>& setDefault(const T& value) {
            Value<T>::setDefault(value);

            return *this;
        }
    };

} // end of console namespace
} // end of hyper namespace
