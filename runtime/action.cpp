#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/actions/action.hpp>

using namespace fabulist::runtime;

void action::execute(state& state) const
{
    _impl->execute(state);
}

std::string action::type() const
{
    return _impl->type();
}


actions::action* action::operator->()
{
    return _impl.get();
}
actions::action const* action::operator->() const
{
    return _impl.get();
}

actions::action* action::operator*()
{
    return _impl.get();
}
actions::action const* action::operator*() const
{
    return _impl.get();
}
