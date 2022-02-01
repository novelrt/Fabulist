#include "compiler.hpp"

using namespace fabulist::compiler::detail;

compiler::compiler()
    : state{luaL_newstate()}
{ }
compiler::~compiler() noexcept
{
    lua_close(state);
}
