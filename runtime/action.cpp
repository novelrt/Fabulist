#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/action_private.hpp>

using namespace fabulist::runtime;

action::action(detail::action* pimpl)
    : _pimpl{pimpl}
{ }

action::~action() noexcept = default;
action::action(action&&) = default;
action& action::operator=(action&&) = default;

std::string action::type()
{
    return _pimpl->type;
}
