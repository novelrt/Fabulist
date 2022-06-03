#ifndef LUA_HPP
#define LUA_HPP

// HACK: this is super duper naughty...
#define lua_load _lua_load

#include <lua.h>
#include <lauxlib.h>

// Return definitions to normal
#undef lua_load
// And just to make sure, overwrite the renamed ones
#define _lua_load(...) static_assert(false, "use lua_load")

/// THIS MUST BE CALLED AFTER CREATING A NEW STATE OR ELSE LUA WILL BE VERY SAD
int luaopen_compat(lua_State* L);

int lua_load(lua_State* L, lua_Reader reader, void* data, char const* source, char const* mode);

#if LUA_VERSION_NUM == 501
// Lua 5.1

// Cannot undef LUA_GLOBALSINDEX as it breaks lua_upvalueindex
// #undef LUA_GLOBALSINDEX
#undef LUA_ENVIRONINDEX

#define LUA_RIDX_MAINTHREAD 1
#define LUA_RIDX_GLOBALS 2
#define LUA_RIDX_LAST LUA_RIDX_GLOBALS

#define lua_getfenv(...) static_assert(false, "lua_getfenv is not supported after lua 5.1")
#define lua_setfenv(...) static_assert(false, "lua_setfenv is not supported after lua 5.1")
#define luaL_register(...) static_assert(false, "use luaL_setfuncs instead")
#define luaL_typerror(...) static_assert(false, "luaL_typerror is not supported after lua 5.1")
#define lua_cpall(...) static_assert(false, "use lua_pushcfunction and lua_pcall")
#define lua_equal(...) static_assert(false, "use lua_compare instead")
#define lua_lessthan(...) static_assert(false, "use lua_compare instead")
#define lua_objlen(...) static_assert(false, "use lua_rawlen instead")
#define lua_rawlen(...) (lua_objlen)(__VA_ARGS__)

void luaL_setfuncs(lua_State* L, luaL_Reg const* reg, int nup);
void lua_resume(lua_State* L, lua_State* from, int nargs);

#elif LUA_VERSION_NUM == 502

int lua_cpcall(lua_State* L, lua_CFunction func, void* ud);

#elif LUA_VERSION_NUM == 503

int lua_cpcall(lua_State* L, lua_CFunction func, void* ud);

#elif LUA_VERSION_NUM == 504

int lua_cpcall(lua_State* L, lua_CFunction func, void* ud);

#endif

#endif /* LUA_HPP */
