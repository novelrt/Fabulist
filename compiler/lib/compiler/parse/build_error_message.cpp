#include <algorithm>
#include <iterator>
#include <numeric>

#include "../compiler.hpp"
#include "common.hpp"

std::string build_error_message(error_handler_result* result)
{
    std::vector<std::string> lines{result->message};
    std::transform(
        result->frames.begin(), result->frames.end(),
        std::back_inserter(lines),
        [](const frame& frame) -> std::string
        {
            std::string result;
            std::string::size_type result_size = 4; // '\tat '

            if (frame.name != "")
            {
                result_size += frame.name.size();
                result_size += 4; // ' in '
            }

            result_size += frame.source.size();

            if (frame.line >= 0)
            {
                std::string line = std::to_string(frame.line);
                result_size += 6; // ':line '
            result_size += line.size();
            }

            result.reserve(result_size);

            result.append("\tat ");

            if (frame.name != "")
            {
                result.append(frame.name);
                result.append(" in ");
            }

            result.append(frame.source);

            if (frame.line >= 0)
            {
                result.append(":line ");
                result.append(std::to_string(frame.line));
            }

            return result;
        });

    size_t size = std::accumulate(
        lines.begin(), lines.end(),
        0,
        [](size_t l, const std::string& r){
            return l + r.size();
        });

    std::string message;
    message.reserve(size + lines.size()); // size of bytes + newlines
    std::for_each(
        lines.begin(), lines.end(),
        [&message](const std::string& line){
            message.append(line);
            message.append("\n");
        });

    return message;
}
