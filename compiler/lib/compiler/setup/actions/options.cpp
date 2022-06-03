#include "../actions.hpp"

static int create_options_action(lua_State* L);
static int create_options_multiple(lua_State* L)
{
    luaL_checkstring(L, 1);
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_pushcclosure(L, &create_options_action, 2);
    return 1;
}

static int create_options_action(lua_State* L)
{
    if (lua_type(L, 1) != LUA_TTABLE)
    {
        const char* message = lua_pushfstring(L,
            "table expected, got %s",
            luaL_typename(L, 1));

        return luaL_argerror(L, 1, message);
    }

    lua_pushvalue(L, lua_upvalueindex(2));

    lua_pushliteral(L, "options");
    lua_gettable(L, -2);

    size_t length = lua_rawlen(L, -1);

    lua_createtable(L, 0, 2);

    lua_pushliteral(L, "name");
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_settable(L, -3);

    lua_pushliteral(L, "actions");
    lua_pushvalue(L, 1);
    lua_settable(L, -3);

    lua_rawseti(L, -2, (int)length + 1);

    lua_pop(L, 1);

    lua_pushcclosure(L, &create_options_multiple, 1);
    return 1;
}

template <>
int call_action<action::options>(lua_State* L)
{
    luaL_checkstring(L, 1);

    lua_pushvalue(L, LUA_REGISTRYINDEX);
    lua_pushliteral(L, "current_section");
    lua_rawget(L, -2);

    size_t length = lua_rawlen(L, -1);

    lua_createtable(L, 0, 2);
    lua_pushvalue(L, -1);

    lua_rawseti(L, -3, (int)length + 1);
    lua_remove(L, -2);
    lua_remove(L, -2);

    lua_pushliteral(L, "type");
    lua_pushliteral(L, "options");
    lua_settable(L, -3);

    lua_pushliteral(L, "options");
    lua_createtable(L, 1, 0);
    lua_settable(L, -3);

    lua_pushcclosure(L, &create_options_action, 2);
    return 1;
}
