#include "../actions.hpp"

template <>
int call_action<action::jump>(lua_State* L)
{
    luaL_checkstring(L, 1);

    lua_createtable(L, 0, 2);
    lua_pushliteral(L, "section");
    lua_pushvalue(L, 1);
    lua_settable(L, -3);

    lua_pushliteral(L, "type");
    lua_pushliteral(L, "jump");
    lua_settable(L, -3);

    return 1;
}
