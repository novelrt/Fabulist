#include "common.hpp"

static luaL_Reg builtins[] = {
    { "speaker", create_speaker },
    { "section", create_section },
    { "options", create_options },
    { nullptr, nullptr }
};

int setup_state(lua_State* L)
{
    lua_pushvalue(L, LUA_REGISTRYINDEX); // +registry

    lua_rawgeti(L, -1, LUA_RIDX_GLOBALS); // +globals
    luaL_setfuncs(L, builtins, 0);

    lua_newtable(L); // speakers

    lua_newtable(L); // mt
    lua_pushliteral(L, "__index"); // k
    lua_pushvalue(L, -3); // v
    lua_rawset(L, -3); // mt[k] = v
    lua_setmetatable(L, -3); // metatable(globals) = mt

    lua_remove(L, -2); // -globals

    lua_pushliteral(L, "speakers"); // k
    lua_pushvalue(L, -2); // v
    lua_rawset(L, -4); // t[k] = v

    lua_pop(L, 1); // -speakers table

    lua_pushliteral(L, "sections"); // k
    lua_newtable(L); // v
    lua_rawset(L, -3); // t[k] = v

    lua_pop(L, 1); // -registry

    return 0;
}
