#ifndef VERSION_HPP
#define VERSION_HPP

#include <string_view>
#include <tuple>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

FABULIST_RUNTIME_EXPORT std::tuple<int, int, int> get_version();
FABULIST_RUNTIME_EXPORT std::string_view get_version_string();

}

#endif /* VERSION_HPP */
