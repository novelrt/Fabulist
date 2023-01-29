#ifndef LOAD_EXCEPTION_HPP
#define LOAD_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace fabulist::runtime
{

class load_exception : public std::runtime_error
{
    public:
        explicit load_exception(std::string const& what,
            std::string const& name)
            : runtime_error{ what },
            _name{name}
        {};

        ~load_exception() noexcept = default;
        load_exception(const load_exception&) = default;
        load_exception& operator=(const load_exception&) = default;
        load_exception(load_exception&&) = default;
        load_exception& operator=(load_exception&&) = default;

        std::string name() const { return _name; }

    private:
        std::string _name;
};

}

#endif /* LOAD_EXCEPTION_HPP */
