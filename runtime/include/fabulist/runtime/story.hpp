#ifndef STORY_HPP
#define STORY_HPP

#include <filesystem>
#include <istream>
#include <memory>
#include <vector>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class section;
class state;

namespace detail
{

class story;

}

class FABULIST_RUNTIME_EXPORT story
{
    public:
        explicit story();
        ~story() noexcept;
        story(const story&) = delete;
        story& operator=(const story&) = delete;
        story(story&&);
        story& operator=(story&&);


        state create_state(std::string section);
        std::vector<section> const& get_sections();

    private:
        std::unique_ptr<detail::story> _pimpl;
};

story parse_story(std::filesystem::path path);
story parse_story(std::istream& stream);

}

#endif /* STORY_HPP */
