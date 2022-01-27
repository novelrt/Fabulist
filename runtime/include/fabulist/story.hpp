#ifndef FABULIST_STORY_HPP
#define FABULIST_STORY_HPP

#include <string>
#include <istream>
#include <memory>

#include <fabulist_export.hpp>

namespace fabulist
{

namespace detail
{

struct story_impl;

};

class FABULIST_RUNTIME_EXPORT speaker;
class FABULIST_RUNTIME_EXPORT state;

/**
 * Defines a type used to represent a story in its entirety.
 * 
 * This type does not include any sort of state
 */
class FABULIST_RUNTIME_EXPORT story
{
    public:
        /**
         * Creates a state which can be used to execute this story
         * 
         * @param section The section to begin executing from.
         */
        state create_state(std::string section);

        ~story() noexcept;
        story(const story&) = delete;
        story& operator=(const story&) = delete;
        story(story&&);
        story& operator=(story&&);

        speaker const* add_speaker(std::string name);
        speaker const* get_speaker(std::string name);

    private:
        friend struct detail::story_impl;
        std::unique_ptr<detail::story_impl> _impl;

        explicit story();

        friend story load_story_from_stream(std::istream&);
};

/**
 * Loads a story from the given stream. This could be from the filesystem, a
 * virtual filesystem, a network request or an in-memory buffer.
 * 
 * @param stream The stream to load the story from.
 */
story FABULIST_RUNTIME_EXPORT load_story_from_stream(std::istream& stream);

}

#endif /* FABULIST_STORY_HPP */
