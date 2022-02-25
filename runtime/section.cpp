#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>

using namespace fabulist::runtime;

class detail::section
{

};

section::section()
    : _pimpl{new detail::section{}}
{ }
section::~section() noexcept = default;
section::section(section&&) = default;
section& section::operator=(section&&) = default;

std::string section::get_name()
{
    return "temporary name";
}
