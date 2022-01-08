#ifndef FABULIST_SPEAKER_HPP
#define FABULIST_SPEAKER_HPP

#include <string>
#include <memory>

#include <fabulist_export.hpp>

namespace fabulist
{

namespace detail
{

struct speaker_impl;

}

/**
 * Defines a type used to represent a speaker within a story.
 */
class FABULIST_RUNTIME_EXPORT speaker
{
    public:
        /**
         * Gets the name of this speaker.
         *
         * @return The name of the speaker
         */
        std::string get_name() const;

        explicit speaker(std::string name);
        ~speaker() noexcept;
        speaker(const speaker&) = delete;
        speaker& operator=(const speaker&) = delete;
        speaker(speaker&&);
        speaker& operator=(speaker&&);


    private:
        friend struct detail::speaker_impl;
        std::unique_ptr<detail::speaker_impl> _impl;
};

}

#endif /* FABULIST_SPEAKER_HPP */
