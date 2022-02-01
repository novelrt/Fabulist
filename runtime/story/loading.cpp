#include <vector>

#include <fabulist/speaker.hpp>
#include <fabulist/story.hpp>

#include <sol/sol.hpp>

#include <story_impl.hpp>

#include <iostream>

using namespace fabulist;

struct reader {
    std::istream& stream;
    std::vector<char> buffer;
};

const char* read_func(lua_State*, void* data, size_t* size)
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

story fabulist::load_story_from_stream(std::istream& stream)
{
    story story;

    reader tmpReader{stream, std::vector<char>(4096)};
    auto code = story._impl->L.safe_script(read_func, &tmpReader, "story");

    return story;
}
