#include "../actions.hpp"

int setup_parameters(lua_State* L);

template <>
int call_action<action::call>(lua_State* L)
{
    luaL_checkstring(L, 1);

    lua_createtable(L, 0, 2);
    lua_pushliteral(L, "method");
    lua_pushvalue(L, 1);
    lua_settable(L, -3);

    lua_pushliteral(L, "type");
    lua_pushliteral(L, "call");
    lua_settable(L, -3);

    lua_pushliteral(L, "parameters");
    lua_newtable(L);
    lua_settable(L, -3);

    lua_pushcclosure(L, &setup_parameters, 1);
    return 1;
}

int setup_parameters(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_pushvalue(L, lua_upvalueindex(1));
    lua_pushliteral(L, "parameters");
    lua_pushvalue(L, 1);
    lua_settable(L, -3);

    return 1;
}
