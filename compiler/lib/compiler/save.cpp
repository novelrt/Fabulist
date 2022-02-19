#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <string>
#include <variant>

#include <nlohmann/json.hpp>

#include <fabulist/compiler/compiler.hpp>
#include <fabulist/compiler/section.hpp>

#include "compiler.hpp"

using namespace fabulist::compiler;

template <typename Container>
bool is_contiguous(Container value)
{
    const auto& found = std::adjacent_find(
        value.begin(), value.end(),
        [](const auto& left, const auto& right)
        {
            if (std::holds_alternative<double>(left.first) &&
                std::holds_alternative<double>(right.first))
            {
                return std::get<double>(right.first) - std::get<double>(left.first) != 1;
            }
            else
            {
                return true;
            }
        });

    return found == value.end();
}

nlohmann::json to_json(lua_State* L);
nlohmann::json table_to_json(lua_State* L)
{
    std::map<std::variant<double, std::string>, nlohmann::json> values;
    bool is_array = true;

    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        if (lua_type(L, -2) == LUA_TNUMBER)
        {
            auto index = lua_tonumber(L, -2);
            is_array = is_array && ((lua_Number)(size_t)index == index) && is_contiguous(values);
            values.emplace(lua_tonumber(L, -2), to_json(L));
        }
        else if (lua_type(L, -2) == LUA_TSTRING)
        {
            is_array = false;

            size_t key_size;
            char const* key_str = lua_tolstring(L, -2, &key_size);
            std::string key{key_str, key_size};

            values.emplace(key, to_json(L));
        }
        else
        {
            lua_pop(L, 3);
            throw std::runtime_error { "expected string or number for key" };
        }

        lua_pop(L, 1); // pop value for next iteration
    }

    nlohmann::json result = std::accumulate(
        values.begin(), values.end(),
        nlohmann::json{},
        [is_array](nlohmann::json& result,
            decltype(values)::const_reference value)
        {
            if (is_array)
            {
                result.push_back(value.second);
            }
            else
            {
                std::visit([&result, &value = value.second](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, double>)
                    {
                        result[std::to_string(arg)] = value;
                    }
                    else if constexpr (std::is_same_v<T, std::string>)
                    {
                        result[arg] = value;
                    }
                }, value.first);
            }

            return result;
        });

    return result;
}

nlohmann::json to_json(lua_State* L)
{
    nlohmann::json result;

    switch (lua_type(L, -1))
    {
        case LUA_TNIL:
            result = nullptr;
            break;
        case LUA_TBOOLEAN:
            result = static_cast<bool>(lua_toboolean(L, -1));
            break;
        case LUA_TNUMBER:
            result = lua_tonumber(L, -1);
            break;
        case LUA_TSTRING:
        {
            size_t size;
            char const* value = lua_tolstring(L, -1, &size);
            result = std::string{value, size};
            break;
        }
        case LUA_TTABLE:
        {
            result = table_to_json(L);
            break;
        }
        default:
            throw std::runtime_error{"Unhandled type"};
    }

    return result;
}

void compiler::save(std::ostream& stream)
{
    lua_pushvalue(_pimpl->state, LUA_REGISTRYINDEX);
    lua_pushliteral(_pimpl->state, "sections");
    lua_rawget(_pimpl->state, -2);

    stream << to_json(_pimpl->state);
}
