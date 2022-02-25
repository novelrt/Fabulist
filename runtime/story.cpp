#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>
#include <fabulist/runtime/story.hpp>

using namespace fabulist::runtime;

class detail::story
{
    public:
        std::vector<runtime::section> sections;
};

story::story()
    : _pimpl{new detail::story{}}
{ }
story::~story() noexcept = default;
story::story(story&&) = default;
story& story::operator=(story&&) = default;

state story::create_state(std::string)
{
    return state{};
}

std::vector<section> const& story::get_sections()
{
    return _pimpl->sections;
}
