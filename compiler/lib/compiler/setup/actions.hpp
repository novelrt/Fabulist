#ifndef SETUP_ACTIONS_COMMON_HPP
#define SETUP_ACTIONS_COMMON_HPP

#include "common.hpp"

#define ACTIONS \
ACTION(jump)

enum class action
{
    #define ACTION(name) name,
    ACTIONS
    #undef ACTION
};

template <action Action>
int call_action(lua_State* L);

#endif /* SETUP_ACTIONS_COMMON_HPP */
