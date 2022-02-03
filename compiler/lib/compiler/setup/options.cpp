#include "common.hpp"

static int create_options_action(lua_State* L)
{
    size_t size;
    const char* text = luaL_checklstring(L, lua_upvalueindex(1), &size);

    (void)text;

    if (lua_type(L, 1) != LUA_TTABLE)
    {
        const char* message = lua_pushfstring(L,
                                              "table expected, got %s",
                                              luaL_typename(L, 1));

        return luaL_argerror(L, 1, message);
    }

    lua_pushcfunction(L, &create_options);
    return 1;
}

int create_options(lua_State* L)
{
    size_t size;
    const char* text = luaL_checklstring(L, 1, &size);

    (void)text;

    lua_pushcclosure(L, &create_options_action, 1);
    return 1;
}

int setup_options(lua_State*)
{
    return 0;
}
