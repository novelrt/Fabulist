#ifndef ACTIONS_ACTION_HPP
#define ACTIONS_ACTION_HPP

#include <string>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class state;

}

namespace fabulist::runtime::actions
{

class FABULIST_RUNTIME_EXPORT action
{
    public:
        explicit action() = default;
        virtual ~action() noexcept = default;
        // TODO: should these be = delete?
        action(const action&) = default;
        action& operator=(const action&) = default;
        action(action&&) = default;
        action& operator=(action&&) = default;

        virtual void execute(state&) const = 0;
        virtual std::string type() const noexcept = 0;
};

}

#endif /* ACTIONS_ACTION_HPP */
