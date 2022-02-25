#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/story.hpp>

using namespace fabulist::runtime;

class detail::story
{
    public:
        std::vector<section> sections;
};

std::vector<section> story::get_sections()
{
    return _pimpl->sections;
}
