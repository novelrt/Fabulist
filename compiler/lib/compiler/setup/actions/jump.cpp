#include <string_view>

#include "../actions.hpp"

constexpr std::pair<std::string_view, std::string_view> values[] = {
    {"type", "action"},
    {"action", "jump"}
};

template <>
int call_action<action::jump>(lua_State* L)
{
    luaL_checkstring(L, 1);

    lua_createtable(L, 0, 1 + (int)std::size(values));
    lua_pushliteral(L, "section");
    lua_pushvalue(L, 1);
    lua_settable(L, -3);

    for (auto& pair : values)
    {
        lua_pushlstring(L, pair.first.data(), pair.first.size());
        lua_pushlstring(L, pair.second.data(), pair.second.size());
        lua_settable(L, -3);
    }

    return 1;
}
