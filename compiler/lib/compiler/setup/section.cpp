#include "common.hpp"

int create_section(lua_State* L)
{
    size_t size;
    char const* name = luaL_checklstring(L, 1, &size);

    (void)name;

    lua_pushvalue(L, LUA_REGISTRYINDEX); // +registry

    lua_pushliteral(L, "speakers"); // k
    lua_rawget(L, -2); // t[k]

    lua_pushvalue(L, 1); // k
    lua_newtable(L); // v
    lua_rawset(L, -3); // t[k] = v

    lua_pop(L, 1); // -registry

    return 0;
}

int setup_section(lua_State*)
{
    return 0;
}
