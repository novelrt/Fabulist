#include <string_view>

#include "common.hpp"

constexpr std::pair<std::string_view, std::string_view> values[] = {
    {"type", "line"},
};

static int speaker_line(lua_State* L)
{
    size_t line_size;
    char const* line = luaL_checklstring(L, 1, &line_size);
    size_t speaker_size;
    char const* speaker = luaL_checklstring(L,
                                            lua_upvalueindex(1),
                                            &speaker_size);

    (void)line;
    (void)speaker;

    lua_createtable(L, 0, 1 + (int)std::size(values));

    lua_pushliteral(L, "text");
    lua_pushvalue(L, 1);
    lua_settable(L, -3);

    lua_pushliteral(L, "speaker");
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_settable(L, -3);

    for (auto& pair : values)
    {
        lua_pushlstring(L, pair.first.data(), pair.first.size());
        lua_pushlstring(L, pair.second.data(), pair.second.size());
        lua_settable(L, -3);
    }

    lua_pushvalue(L, LUA_REGISTRYINDEX); // +registry

    lua_pushliteral(L, "current_section"); // k
    lua_rawget(L, -2); // registry[k]
    size_t size = lua_rawlen(L, -1); // #registry[k]
    lua_pushvalue(L, -3); // v
    lua_rawseti(L, -2, size + 1); // registry[k][#registry[k] + 1] = v

    lua_pop(L, 1);

    lua_pushliteral(L, "speakers"); // k
    lua_rawget(L, -2); // registry[k]
    lua_pushvalue(L, lua_upvalueindex(1)); // k2
    lua_rawget(L, -2); // registry[k][k2]

    lua_remove(L, -2); // -registry[k]
    lua_remove(L, -2); // -registry

    return 1;
}

int create_speaker(lua_State* L)
{
    size_t size;
    char const* name = luaL_checklstring(L, 1, &size);

    (void)name;

    lua_pushvalue(L, LUA_REGISTRYINDEX); // registry

    lua_pushliteral(L, "speakers"); // k
    lua_rawget(L, -2); // registry[k]

    lua_pushvalue(L, 1); // k

    lua_pushvalue(L, -1);
    lua_pushcclosure(L, &speaker_line, 1); // v

    lua_rawset(L, -3); // t[k] = v

    lua_pop(L, 2); // pop speakers and registry

    return 0;
}

int setup_speaker(lua_State*)
{
    return 0;
}
