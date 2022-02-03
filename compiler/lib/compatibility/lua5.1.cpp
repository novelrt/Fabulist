// DO NOT INCLUDE "lua.hpp" HERE! THIS WILL BREAK EVERYTHING!

#include <cstdlib>

#include <lua.h>
#include <lauxlib.h>

static_assert(LUA_VERSION_NUM == 501, "Do not compile this outside of Lua 5.1");

int luaopen_compat(lua_State* L)
{
    lua_pushvalue(L, LUA_REGISTRYINDEX); // +registry

    lua_pushthread(L); // +thread
    int ref = luaL_ref(L, -2); // -thread
    if (ref != 1) std::abort();

    lua_pushvalue(L, LUA_GLOBALSINDEX); // +globals
    ref = luaL_ref(L, -2); // -globals
    if (ref != 2) std::abort();

    lua_pop(L, 1); // -registry

    return 0;
}


// Effectively just a port from 5.2 lauxlib.c
void luaL_setfuncs(lua_State* L, luaL_Reg const* reg, int nup)
{
    luaL_checkstack(L, nup, "too many upvalues");

    for (luaL_Reg const* value = reg; value->name != nullptr; value++)
    {
        for (int i = 0; i < nup; i++)
            lua_pushvalue(L, -nup);
        lua_pushcclosure(L, value->func, nup);
        lua_setfield(L, -(nup + 2), value->name);
    }

    lua_pop(L, nup);
}

int lua_load(lua_State* L, lua_Reader reader, void* data, const char* source,
    const char* mode)
{
    (void) mode; // N.B. mode is ignored in 5.1, so we'll ignore it here too.
    return lua_load(L, reader, data, source);
}
