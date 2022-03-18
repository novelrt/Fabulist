#include <cstring>
#include <iostream>

#include "common.hpp"

static luaL_Reg builtins[] = {
    { "speaker", create_speaker },
    { "section", create_section },
    { nullptr, nullptr }
};

void push_to_section(lua_State* L, lua_Debug* ar)
{
    if (ar->event == LUA_HOOKRET)
    {
        lua_getinfo(L, "S", ar);

        int top = lua_gettop(L);

        if (lua_type(L, top) == LUA_TTABLE)
        {
            lua_pushvalue(L, LUA_REGISTRYINDEX);
            lua_pushliteral(L, "return");
            lua_pushvalue(L, top);
            lua_rawset(L, -3);
            lua_pop(L, 1);
        }
        else if (strcmp(ar->what, "main") != 0)
        {
            lua_pushvalue(L, LUA_REGISTRYINDEX);
            lua_pushliteral(L, "return");
            lua_pushnil(L);
            lua_rawset(L, -3);
            lua_pop(L, 1);
        }
    }
    else if (ar->event == LUA_HOOKLINE)
    {
        lua_pushvalue(L, LUA_REGISTRYINDEX);
        lua_pushliteral(L, "return");
        lua_rawget(L, -2);

        if (!lua_isnil(L, -1))
        {
            lua_pushliteral(L, "current_section");
            lua_rawget(L, -3);

            size_t length = lua_rawlen(L, -1);

            lua_pushvalue(L, -2);
            lua_rawseti(L, -2, (int)length + 1);
            lua_pop(L, 1);
        }

        lua_pop(L, 1);
        lua_pushliteral(L, "return");
        lua_pushnil(L);
        lua_rawset(L, -3);
        lua_pop(L, 1);
    }
}

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

    lua_sethook(L, push_to_section, LUA_MASKRET | LUA_MASKLINE, 0);

    return 0;
}
