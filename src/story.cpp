#include <string>

#include <fabulist/speaker.hpp>
#include <fabulist/story.hpp>

#include <sol/sol.hpp>

#include <story_impl.hpp>

using namespace fabulist;

story::story()
    : _impl(std::make_unique<detail::story_impl>(this))
{ }

story::~story() noexcept = default;
story::story(story&&) = default;
story& story::operator=(story&&) = default;

speaker const* story::add_speaker(std::string name)
{
    auto [spk, succ] = _impl->speakers.emplace(name, std::make_unique<speaker>(name));

    return spk->second.get();
}

speaker const* story::get_speaker(std::string name)
{
    auto it = _impl->speakers.find(name);

    if (it != _impl->speakers.end())
    {
        return it->second.get();
    }

    return nullptr;
}
