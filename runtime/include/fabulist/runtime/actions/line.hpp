#ifndef ACTIONS_LINE_HPP
#define ACTIONS_LINE_HPP

#include <fabulist/runtime/action.hpp>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime::actions
{

namespace detail
{

class line;

}

class FABULIST_RUNTIME_EXPORT line : public action
{
    public:
        explicit line();
        ~line() noexcept override;
        line(const line&) = delete;
        line& operator=(const line&) = delete;
        line(line&&);
        line& operator=(line&&);

};

}

#endif /* ACTIONS_LINE_HPP */
