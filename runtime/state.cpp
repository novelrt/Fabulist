#include <string>
#include <unordered_map>

#include <fabulist/runtime/state.hpp>

using namespace fabulist::runtime;

class detail::state
{
    public:
        std::unordered_map<std::string, std::any> variables;
};

state::state()
    : _pimpl{new detail::state{}}
{ }

state::~state() noexcept = default;
state::state(state&&) = default;
state& state::operator=(state&&) = default;

std::any state::get_variable(std::string variable)
{
    auto [it, inserted] = _pimpl->variables.try_emplace(variable, std::any{});

    return *it;
}
