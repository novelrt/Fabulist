#include <unordered_map>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>
#include <fabulist/runtime/story.hpp>

using namespace fabulist::runtime;

struct detail::state
{
    size_t action_index;
    runtime::section const* current_section;
    runtime::story const* story;
    ::state::query_callback_type query_callback;
    std::unordered_map<std::string, std::any> variables;
};

state::state(query_callback_type query_callback, class story const* story, class section const* section)
    : _pimpl{new detail::state{0, section, story, query_callback, {}}}
{ }

state::~state() noexcept = default;
state::state(state&&) = default;
state& state::operator=(state&&) = default;

std::any state::get_variable(std::string variable)
{
    auto [it, inserted] = _pimpl->variables.try_emplace(variable, std::any{});

    return *it;
}

story const* state::story() const noexcept
{
    return _pimpl->story;
}

section const* state::section() const noexcept
{
    return _pimpl->current_section;
}

void state::jump_to_section(std::string const& section)
{
    _pimpl->current_section = _pimpl->story->get_section(section);
    _pimpl->action_index = 0;
}

std::vector<std::string>::iterator state::query(
    std::vector<std::string>& options) const
{
    return std::find(options.begin(), options.end(),
        _pimpl->query_callback(options));
}

state::state_update state::update()
{
    return state::state_update{this};
}

state::state_update::operator bool() const noexcept
{
    return _state->move_next();
}

state::state_update::operator action const&() const noexcept
{
    return _state->get_current_action();
}

action const& state::state_update::operator*() const noexcept
{
    return _state->get_current_action();
}

action const& state::state_update::operator->() const noexcept
{
    return _state->get_current_action();
}

bool state::move_next()
{
    if (_pimpl->action_index >= _pimpl->current_section->size())
        return false;

    _pimpl->action_index++;
    return true;
}

action const& state::get_current_action() const noexcept
{
    return _pimpl->current_section->at(_pimpl->action_index - 1);
}
