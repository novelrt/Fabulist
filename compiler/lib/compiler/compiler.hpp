#ifndef COMPILER_PRIVATE_HPP
#define COMPILER_PRIVATE_HPP

#include <vector>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
}

#include "fabulist_compiler_export.hpp"

namespace fabulist::compiler
{

class section;

}

namespace fabulist::compiler::detail
{

class compiler
{
    public:
        explicit compiler();
        ~compiler() noexcept;
        compiler(const compiler&) = delete;
        compiler& operator=(const compiler&) = delete;
        compiler(compiler&&) = default;
        compiler& operator=(compiler&&) = default;

        lua_State* state;
        //std::vector<section> sections;
};

}

#endif /* COMPILER_PRIVATE_HPP */
