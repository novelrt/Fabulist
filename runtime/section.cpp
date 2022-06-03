#include <fabulist/runtime/actions/action.hpp>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>

using namespace fabulist::runtime;

struct detail::section
{
    std::string name;
    std::vector<action> actions;
};

section::section(std::string const& name, std::vector<action>&& actions)
    : _pimpl{new detail::section{name, std::move(actions)}}
{ }
section::~section() noexcept = default;
section::section(section&&) = default;
section& section::operator=(section&&) = default;

std::string section::name() const noexcept
{
    return _pimpl->name;
}

action const& section::at(size_t index) const noexcept
{
    return _pimpl->actions.at(index);
}

action const& section::operator[](size_t index) const noexcept
{
    return at(index);
}

std::vector<action>::const_iterator section::begin() const noexcept
{
    return _pimpl->actions.cbegin();
}

std::vector<action>::const_iterator section::end() const noexcept
{
    return _pimpl->actions.cend();
}

size_t section::size() const noexcept
{
    return _pimpl->actions.size();
}
