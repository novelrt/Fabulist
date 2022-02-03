#include <array>
#include <cassert>
#include <cstring>
#include <exception>

#include <iostream>

#include <fabulist/compiler/compiler.hpp>

#include "compiler.hpp"
#include "parse/common.hpp"

using namespace fabulist::compiler;

struct reader {
    std::istream& stream;
    std::array<char, 1024> buffer;
};

char const* read_func(lua_State*, void* data, size_t* size)
{
    auto* reader = static_cast<struct reader*>(data);

    if (reader->stream)
    {
        auto read = reader->stream.readsome(
            reader->buffer.data(), reader->buffer.size());

        *size = read;
        return reader->buffer.data();
    }

    return nullptr;
}

int error_handler(lua_State* L)
{
    std::string message{"(error message not a string)"};

    if (lua_type(L, -1) == LUA_TSTRING)
    {
        // lua_tolstring changes the type on the stack, so we avoid it here
        size_t length;
        const char* result = lua_tolstring(L, -1, &length);

        message = std::string{result, length};
    }

    std::vector<frame> traceback = get_traceback(L);

    auto result = static_cast<error_handler_result*>(
        lua_newuserdata(L, sizeof(error_handler_result)));

    // initialize the struct in-place
    new (result) error_handler_result{message, traceback};
    return 1;
}

void compiler::parse(std::istream& stream, std::string name)
{
    reader reader{stream, {}};

    lua_pushcclosure(_pimpl->state, error_handler, 0);

    int status =
#if LUA_VERSION_NUM == 501
        lua_load(_pimpl->state, read_func, &reader, name.c_str(), "t");
#endif

    if (status) error_handler(_pimpl->state);
    else status =
#if LUA_VERSION_NUM == 501
        lua_pcall(_pimpl->state, 0, 0, -2);
#endif

    if (status)
    {
        assert(lua_type(_pimpl->state, -1) == LUA_TUSERDATA
            && "Somehow the top of the stack wasn't a userdata...");

        auto result = static_cast<error_handler_result*>(
            lua_touserdata(_pimpl->state, -1));

        std::string message{build_error_message(result)};

        switch (status)
        {
            case LUA_ERRRUN:
                throw std::runtime_error{message};
            case LUA_ERRMEM:
                throw std::bad_alloc{};
            case LUA_ERRSYNTAX:
                throw std::runtime_error{message};
        }

        // this is important as otherwise it won't get destructed,
        // which is bad for obvious reasons
        result->~error_handler_result();
    }
}
