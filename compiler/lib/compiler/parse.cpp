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
    std::string name;
    std::array<char, 1024> buffer;
};

char const* read_func(lua_State*, void* data, size_t* size)
{
    auto* reader = static_cast<struct reader*>(data);

    if (reader->stream)
    {
        if (reader->stream.rdbuf()->in_avail() > 0)
        {
            // Attempt to read out of the buffer without blocking if we can
            auto read = reader->stream.readsome(
                reader->buffer.data(), (std::streamsize)reader->buffer.size());

            *size = (std::size_t)read;
        }
        else
        {
            // Otherwise, fall back to a traditional blocking read
            reader->stream.read(reader->buffer.data(), (std::streamsize)reader->buffer.size());

            *size = (std::size_t)reader->stream.gcount();
        }

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

int parse_main(lua_State* L)
{
    void* data = lua_touserdata(L, 1);
    auto* reader = static_cast<struct reader*>(data);

    lua_pushcclosure(L, error_handler, 0);

    if (lua_load(L, read_func, reader, reader->name.c_str(), "t"))
    {
        error_handler(L);
        lua_error(L);
    }
    else if (lua_pcall(L, 0, 0, -2))
    {
        lua_error(L);
    }

    lua_pushvalue(L, LUA_REGISTRYINDEX);
    lua_pushliteral(L, "return");
    lua_rawget(L, -2);

    if (!lua_isnil(L, -1))
    {
        lua_pushliteral(L, "detected that an action may be missed from a section");
        error_handler(L);
        lua_error(L);
    }

    return 0;
}

void compiler::parse(std::istream& stream, std::string name)
{
    reader reader{stream, name, {}};

    int status = lua_cpcall(_pimpl->state, parse_main, &reader);

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
