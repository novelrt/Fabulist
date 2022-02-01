#include <cstring>

#include "../compiler.hpp"
#include "common.hpp"

std::vector<frame> get_traceback(lua_State* L)
{
    std::vector<frame> traceback;

    lua_Debug frame;
    for (int level = 1; lua_getstack(L, level, &frame); level++)
    {
        if (lua_getinfo(L, "nSl", &frame))
        {
            std::string name;
            if (frame.name != nullptr)
            {
                size_t length = strlen(frame.name);
                if (*frame.namewhat == '\0') // empty string
                {
                    // no need to copy or anything, just reallocate
                    name = frame.name;
                }
                else
                {
                    // '(namewhat) name'
                    size_t length_namewhat = strlen(frame.namewhat);
                    name.resize(length + length_namewhat + 1);

                    memcpy(name.data(), frame.namewhat, length_namewhat);
                    name[length_namewhat] = ' ';
                    memcpy(
                        name.data() + length_namewhat + 1, frame.name, length);
                }
            }

            std::string source{frame.short_src};
            if (frame.source[0] == '=' || frame.source[0] == '@')
            {
                source = frame.source + 1;
            }

            traceback.push_back({
                name,
                source,
                frame.currentline >= 0 ? frame.currentline : frame.linedefined
            });
        }
    }

    return traceback;
}
