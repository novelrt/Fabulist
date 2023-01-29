// DO NOT INCLUDE "lua.hpp" HERE! THIS WILL BREAK EVERYTHING!

#include <lua.h>
#include <lauxlib.h>

static_assert(LUA_VERSION_NUM == 504, "Do not compile this outside of Lua 5.1");

int lua_cpcall(lua_State* L, lua_CFunction func, void* ud)
{
    lua_pushcfunction(L, func);

    lua_pushlightuserdata(L, ud);

    return lua_pcall(L, 1, 0, 0);
}
