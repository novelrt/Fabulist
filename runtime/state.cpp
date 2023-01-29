#include <fstream>
#include <typeindex>
#include <unordered_map>

#include <nlohmann/json.hpp>

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
    ::state::parameters state_parameters;
    std::unordered_map<std::string, std::any> variables;
};

template <typename T>
size_t get_version(T state::parameters::*field)
{
    state::parameters tmp{};
    return size_t(ptrdiff_t(&(tmp.*field)) - ptrdiff_t(&tmp)) + sizeof(T);
}

state::parameters validate(state::parameters const& params)
{
    if (params.version <= get_version(&state::parameters::version))
        throw std::runtime_error{"params.version too small"};

    state::parameters result{};

    if (params.version >= get_version(&state::parameters::query_callback))
        result.query_callback = params.query_callback;

    return result;
}

state::state(parameters const& params, class story const* story, class section const* section)
    : _pimpl{new detail::state{0, section, story, validate(params), {}}}
{ }

state::~state() noexcept = default;
state::state(state&&) = default;
state& state::operator=(state&&) = default;

std::any state::get_variable(std::string variable)
{
    auto [it, inserted] = _pimpl->variables.try_emplace(variable, std::any{});

    return *it;
}

story const* state::get_story() const noexcept
{
    return _pimpl->story;
}

section const* state::get_section() const noexcept
{
    return _pimpl->current_section;
}

void state::jump_to_section(std::string const& section)
{
    _pimpl->current_section = _pimpl->story->get_section(section);
    _pimpl->action_index = 0;
}

std::vector<std::string>::const_iterator state::query(
    std::vector<std::string> const& options) const
{
    return _pimpl->state_parameters.query_callback(options);
}

state::state_update state::update()
{
    return state::state_update{this};
}

void state::save(std::filesystem::path path)
{
    std::ofstream file{path};

    save(file);
}

template <typename T, typename Callable>
auto make_encoder(Callable const& callable)
    -> std::pair<const std::type_index, std::function<nlohmann::json(std::any const&)>>
{
    return {
        std::type_index(typeid(T)),
        [callable](std::any const& any)
        {
            if constexpr (std::is_void_v<T>)
                return callable();
            else
                return callable(std::any_cast<T const&>(any));
        }
    };
}

static std::unordered_map<std::type_index, std::function<nlohmann::json(std::any const&)>> encoders
{
    // nil
    make_encoder<void>([]{ return nullptr; }),
    // "string"
    make_encoder<std::string>([](std::string const& str){ return str; }),
    // TODO: lua_Number
    make_encoder<double>([](double d) { return d; }),
    // TODO: integers
    make_encoder<bool>([](bool b){ return b; })
};

void state::save(std::ostream& stream)
{
    nlohmann::json result = nlohmann::json::object();

    //result["story"] = _pimpl->story;
    if (_pimpl->current_section)
    {
        result["section"] = _pimpl->current_section->name();
        result["action"] = _pimpl->action_index;
    }

    result["variables"] = nlohmann::json::object();

    for (auto const& pair : _pimpl->variables)
    {
        if (auto const it = encoders.find(std::type_index(pair.second.type()));
            it != encoders.cend())
            result["variables"][pair.first] = it->second(pair.second);
        else
            // if we get here something horribly wrong has happened
            // as the code which sets values should never allow anything outside
            // of these values to work
            throw std::logic_error{"unknown type to encode"};
    }

    stream << result;
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
