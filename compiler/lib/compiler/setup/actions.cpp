#include "actions.hpp"

static luaL_Reg actions[] = {
#define ACTION(name) { #name, call_action<action::name> },
ACTIONS
#undef ACTION
    { nullptr, nullptr }
};

int setup_actions(lua_State* L)
{
    lua_pushvalue(L, LUA_REGISTRYINDEX); // +registry

    lua_rawgeti(L, -1, LUA_RIDX_GLOBALS); // +globals
    luaL_setfuncs(L, actions, 0);

    lua_pop(L, 2);

    return 0;
}
