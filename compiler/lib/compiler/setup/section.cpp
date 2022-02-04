#include "common.hpp"

int create_section(lua_State* L)
{
    size_t size;
    char const* name = luaL_checklstring(L, 1, &size);

    (void)name;

    lua_pushvalue(L, LUA_REGISTRYINDEX); // registry

    lua_newtable(L); // section

    lua_pushliteral(L, "sections");
    lua_rawget(L, -3); // registry["sections"]

    lua_pushvalue(L, 1); // k
    lua_pushvalue(L, -3); // v
    lua_rawset(L, -3); // registry["sections"][k] = v

    lua_pop(L, 1); // registry["sections"]

    lua_pushliteral(L, "current_section"); // k
    lua_pushvalue(L, -2); // v
    lua_rawset(L, -4); // registry[k] = v

    lua_pop(L, 2); // registry, section

    return 0;
}

int setup_section(lua_State*)
{
    return 0;
}
