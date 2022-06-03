#ifndef ACTION_HPP
#define ACTION_HPP

//#include <any>
//#include <functional>
#include <memory>
#include <string>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

namespace actions
{

class action;

}

class state;

class FABULIST_RUNTIME_EXPORT action
{
    public:
        template <typename Action,
            typename = std::enable_if<std::is_base_of<actions::action, Action>::value>>
        explicit action(Action&& action)
            : _impl{ std::make_unique<Action>(std::forward<Action>(action)) }
        { };
        ~action() noexcept = default;
        action(const action&) = delete;
        action& operator=(const action&) = delete;
        action(action&&) = default;
        action& operator=(action&&) = default;

        std::string type() const;
        void execute(state& state) const;

        actions::action* operator->();
        actions::action const* operator->() const;

        actions::action* operator*();
        actions::action const* operator*() const;

    private:
        std::unique_ptr<actions::action> _impl;
};

}

#endif /* ACTION_HPP */
