#include <fabulist/runtime/actions/line.hpp>
#include <fabulist/runtime/action_private.hpp>

using namespace fabulist::runtime;
using namespace fabulist::runtime::actions;

line::line()
    : action{new runtime::detail::action{}}
{ };
line::~line() noexcept
{ }
line::line(line&&) = default;
line& line::operator=(line&&) = default;
