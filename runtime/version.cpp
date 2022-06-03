#include <fabulist/runtime/version.hpp>

#include "fabulist_runtime_git_version.hpp"

using namespace fabulist;
using namespace fabulist::runtime;

std::string_view runtime::get_version_string()
{
    return version::version_string;
}

std::tuple<int, int, int> fabulist::runtime::get_version()
{
    return {version::major, version::minor, version::patch};
}
