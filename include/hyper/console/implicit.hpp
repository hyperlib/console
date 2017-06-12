// <hyper/console/implicit.hpp> -*- C++ -*-

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

    template<class T>
    class Implicit : public Value<T> {
    public:
        Implicit(const std::string& shortOption, const std::string& longOption, const std::string& description, const T& implicitVal):
            Value<T>(shortOption, longOption, description, implicitVal)
        {
            setType(OptionValue::Optional);
        }

        Implicit(const std::string& shortOption, const std::string& longOption, const std::string& description, const T& implicitVal, T* assignTo):
            Value<T>(shortOption, longOption, description, implicitVal, assignTo)
        {
            setType(OptionValue::Optional);
        }

        Value<T>& assignTo(T* var);

    protected:
        virtual void parse(const std::string& whatOption, const char* value);

        virtual std::string optionToString() const;

        //virtual OptionValue getType() const;

        Value<T>& setDefault(const T& value);
    };
/*
    template<class T>
    Implicit<T>::Implicit(const std::string& shortOption, const std::string& longOption, const std::string& description, const T& implicitVal) :
        Value<T>(shortOption, longOption, description, implicitVal)
    {
        setType(OptionValue::Optional);
    }


    template<class T>
    Implicit<T>::Implicit(const std::string& shortOption, const std::string& longOption, const std::string& description, const T& implicitVal, T* assignTo) :
        Value<T>(shortOption, longOption, description, implicitVal, assignTo)
    {
        setType(OptionValue::Optional);
    }
*/

    /*template<class T>
    OptionValue Implicit<T>::getType() const {
        return OptionValue::Optional;
    }*/


    template<class T>
    void Implicit<T>::parse(const std::string& whatOption, const char* value) {
        if ((value != NULL) && (strlen(value) > 0)) {
            Value<T>::parse(whatOption, value);
        } else {
            this->addValue(this->m_default);
        }
    }


    template<class T>
    std::string Implicit<T>::optionToString() const {
        std::stringstream ss;
        ss << Option::optionToString() << " [=arg(=" << this->m_default << ")]";

        return ss.str();
    }

} // end of console namespace
} // end of hyper namespace
