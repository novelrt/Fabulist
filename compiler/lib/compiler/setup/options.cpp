#include "common.hpp"

static int create_options_action(lua_State* L)
{
    if (lua_type(L, 1) != LUA_TTABLE)
    {
        const char* message = lua_pushfstring(L,
            "table expected, got %s",
            luaL_typename(L, 1));

        return luaL_argerror(L, 1, message);
    }

    lua_pushvalue(L, LUA_REGISTRYINDEX);
    lua_pushliteral(L, "current_section");
    lua_rawget(L, -2);

    size_t length = lua_rawlen(L, -1);

    lua_createtable(L, 0, 3);

    lua_pushliteral(L, "type");
    lua_pushliteral(L, "option");
    lua_settable(L, -3);

    lua_pushliteral(L, "name");
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_settable(L, -3);

    lua_pushliteral(L, "actions");
    lua_pushvalue(L, 1);
    lua_settable(L, -3);

    lua_rawseti(L, -2, length + 1);

    lua_pop(L, 2);

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
