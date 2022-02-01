#include <fabulist/speaker.hpp>

#include <sol/sol.hpp>

#include <speaker_impl.hpp>
#include <story_impl.hpp>

using namespace fabulist::detail;

story_impl::story_impl(story*)
    : L{}, speakers{}
{
    setup_environment(L);
}
