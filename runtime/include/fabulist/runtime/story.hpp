#ifndef STORY_HPP
#define STORY_HPP

#include <memory>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

namespace detail
{

class story;

}

class FABULIST_RUNTIME_EXPORT story
{
    private:
        std::unique_ptr<detail::story> _pimpl;
};

}

#endif /* STORY_HPP */
