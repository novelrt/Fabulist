#include <fabulist/compiler/version.hpp>

#include "fabulist_compiler_git_version.hpp"

using namespace fabulist;
using namespace fabulist::compiler;

std::string_view compiler::get_version_string()
{
    return version::version_string;
}

std::tuple<int, int, int> compiler::get_version()
{
    return {version::major, version::minor, version::patch};
}
