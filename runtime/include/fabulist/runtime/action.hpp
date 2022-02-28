#ifndef ACTION_HPP
#define ACTION_HPP

#include <memory>
#include <string>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

namespace detail
{

class action;

}

class FABULIST_RUNTIME_EXPORT action
{
    public:
        virtual ~action() noexcept;
        action(const action&) = delete;
        action& operator=(const action&) = delete;
        action(action&&);
        action& operator=(action&&);

        std::string type();


    protected:
        explicit action(detail::action* pimpl);

        std::unique_ptr<detail::action> _pimpl;
};

}

#endif /* ACTION_HPP */
