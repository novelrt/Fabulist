#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/runtime.hpp>
#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>
#include <fabulist/runtime/story.hpp>

using namespace fabulist::runtime;

struct detail::story
{
    ::runtime const* runtime;
    std::unordered_map<std::string, ::section> sections;
};

story::story(runtime const* runtime, std::unordered_map<std::string, section>&& sections)
    : _pimpl{new detail::story{runtime, std::move(sections)}}
{ }
story::~story() noexcept = default;
story::story(story&&) = default;
story& story::operator=(story&&) = default;

runtime const* story::get_runtime() const noexcept
{
    return _pimpl->runtime;
}

section const* story::get_section(std::string const& name) const noexcept
{
    return &_pimpl->sections.at(name);
}

state story::create_state(state::parameters const& parameters,  std::string section)
{
    return state{parameters, this, &_pimpl->sections.at(section)};
}
