#ifndef FABULIST_STORY_IMPL_HPP
#define FABULIST_STORY_IMPL_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include <sol/forward.hpp>

#include <fabulist_export.hpp>


namespace fabulist
{

class speaker;
class story;

}

namespace fabulist::detail
{

void setup_environment(sol::state& L);

struct story_impl
{
    sol::state L;
    std::unordered_map<std::string, std::unique_ptr<speaker>> speakers;

    explicit story_impl(story*);
    ~story_impl() noexcept = default;
    story_impl(const story_impl&) = delete;
    story_impl& operator=(const story_impl&) = delete;
    story_impl(story_impl&&) = default;
    story_impl& operator=(story_impl&&) = default;
};

}

#endif /* FABULIST_STORY_IMPL_HPP */
