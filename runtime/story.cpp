#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>
#include <fabulist/runtime/story.hpp>

using namespace fabulist::runtime;

class detail::story
{
    public:
        std::unordered_map<std::string, runtime::section> sections;
};

story::story(std::unordered_map<std::string, section>&& sections)
    : _pimpl{new detail::story{std::move(sections)}}
{ }
story::~story() noexcept = default;
story::story(story&&) = default;
story& story::operator=(story&&) = default;

section const* story::get_section(std::string const& name) const noexcept
{
    return &_pimpl->sections.at(name);
}

state story::create_state(state::query_callback_type query_callback,  std::string section)
{
    return state{query_callback, this, &_pimpl->sections.at(section)};
}
