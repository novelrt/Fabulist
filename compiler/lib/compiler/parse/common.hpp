#ifndef PARSE_COMMON_HPP
#define PARSE_COMMON_HPP

#include <string>
#include <vector>

struct frame
{
    std::string name;
    std::string source;
    int line;
};

struct error_handler_result
{
    std::string message;
    std::vector<frame> frames;
};

std::string build_error_message(error_handler_result* result);
std::vector<frame> get_traceback(lua_State* L);

#endif /* PARSE_COMMON_HPP */
