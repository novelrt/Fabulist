#ifndef STORY_HPP
#define STORY_HPP

#include <filesystem>
#include <istream>
#include <memory>
#include <string>
#include <unordered_map>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class runtime;
class section;
class state;

namespace detail
{

struct story;

}

class FABULIST_RUNTIME_EXPORT story
{
    public:
        explicit story(runtime const* runtime, std::unordered_map<std::string, section>&& sections);
        ~story() noexcept;
        story(const story&) = delete;
        story& operator=(const story&) = delete;
        story(story&&);
        story& operator=(story&&);

        runtime const* get_runtime() const noexcept;

        section const* get_section(std::string const& name) const noexcept;

        state create_state(state::parameters const& parameters, std::string section);

    private:
        std::unique_ptr<detail::story> _pimpl;
};

story parse_story(std::filesystem::path path);
story parse_story(std::istream& stream);

}

#endif /* STORY_HPP */
