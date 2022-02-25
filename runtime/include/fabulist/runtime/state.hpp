#ifndef STATE_HPP
#define STATE_HPP

#include <any>
#include <memory>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

namespace detail
{

class state;

}

class FABULIST_RUNTIME_EXPORT state
{
    public:
        explicit state();
        ~state() noexcept;
        state(const state&) = delete;
        state& operator=(const state&) = delete;
        state(state&&);
        state& operator=(state&&);


        // TODO: is std::any safe here?
        std::any get_variable(std::string variable);

    private:
        std::unique_ptr<detail::state> _pimpl;
};

}

#endif /* STATE_HPP */
