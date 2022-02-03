#include <fabulist/compiler/compiler.hpp>
#include <fabulist/compiler/section.hpp>

#include "compiler.hpp"
#include "setup/common.hpp"

using namespace fabulist::compiler;

static lua_CFunction state_setup_actions[] = {
    &luaopen_compat,
    &setup_state,

    &setup_speaker,
    &setup_section,
    &setup_options,

    &setup_actions,

    nullptr
};

compiler::compiler()
    : _pimpl{new detail::compiler{}}
{
    for (lua_CFunction* action = state_setup_actions; *action != nullptr; action++)
    {
        (*action)(_pimpl->state);
    }
}

compiler::~compiler() noexcept = default;
compiler::compiler(compiler&&) = default;
compiler& compiler::operator=(compiler&&) = default;
