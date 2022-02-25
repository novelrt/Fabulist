#ifndef VERSION_HPP
#define VERSION_HPP

#include <string_view>
#include <tuple>

#include "fabulist_compiler_export.hpp"

namespace fabulist::compiler
{

FABULIST_COMPILER_EXPORT std::tuple<int, int, int> get_version();
FABULIST_COMPILER_EXPORT std::string_view get_version_string();

}

#endif /* VERSION_HPP */
