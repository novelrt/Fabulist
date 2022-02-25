#ifndef STORY_HPP
#define STORY_HPP

#include <memory>
#include <vector>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class section;

namespace detail
{

class story;

}

class FABULIST_RUNTIME_EXPORT story
{
    public:
        std::vector<section> get_sections();

    private:
        std::unique_ptr<detail::story> _pimpl;
};

}

#endif /* STORY_HPP */
