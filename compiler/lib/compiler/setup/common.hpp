#ifndef SETUP_COMMON_HPP
#define SETUP_COMMON_HPP

#include "../compiler.hpp"

int setup_state(lua_State* L);
int setup_section(lua_State* L);
int setup_actions(lua_State* L);

int create_speaker(lua_State* L);
int create_section(lua_State* L);

#endif /* SETUP_COMMON_HPP */
