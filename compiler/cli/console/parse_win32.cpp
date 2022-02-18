#include <iostream>
#include <string_view>

#include "../console.hpp"

std::ostream& cli::detail::usage(std::ostream& stream,
    std::string program_name)
{
    return stream
        << "Usage: " << program_name << " [OPTION]... FILE...\n"
        << "Command line compiler for Fabulist files.\n"
        << "\n"
        << "Arguments:\n"
        << "  FILE         Fabulist file to compile.\n"
        << "\n"
        << "Options:\n"
        << "  /?, /h       Display this help and exit\n"
        << "  /O:OUTPUT    Output file to save generated story\n"
        << "               (default: fabulist.json)\n"
        << "  /v           Enable verbose mode\n";
}

bool find_flag_argument(std::string_view argument, std::string_view value)
{
    if (argument.size() > value.size())
        return false;

    // Remove '/' prefix
    if (value.find("/") != 0)
        return false;

    value.remove_prefix(value.find_first_not_of("/"));

    if (value.find(argument) != 0)
        return false;

    return true;
}

std::optional<std::string_view> find_valued_argument(
    std::string_view argument, std::string_view value)
{
    if (argument.size() > value.size())
        return std::nullopt;

    // Remove '/' prefix
    if (value.find("/") != 0)
        return std::nullopt;

    value.remove_prefix(value.find_first_not_of("/"));

    if (value.find(argument) != 0)
        return std::nullopt;

    value.remove_prefix(argument.size());

    // remove ':' prefix
    if (value.find(":") != 0)
        return std::nullopt;

    value.remove_prefix(value.find_first_not_of(":"));

    return std::make_optional(value);
}

std::optional<cli::parsed_arguments> cli::parse_arguments(
    int argc, char const** argv)
{
    cli::parsed_arguments result;

    cli::detail::set_program_name(argv[0]);

    bool options = true;
    for (int i = 1; i < argc; i++)
    {
        std::string_view argument{argv[i]};

    retry:
        if (options)
        {
            if (find_flag_argument("v", argument))
                result.enable_verbose = true;

            else if (find_flag_argument("?", argument)
                || find_flag_argument("h", argument))
                result.show_usage = true;

            else if (auto output = find_valued_argument("O", argument);
                output.has_value())
                result.output_file = output;

            else if (argument.find_first_not_of("/") == 0)
            {
                options = false;
                goto retry;
            }

            else // invalid command line (i.e. unknown option)
                return std::nullopt;
        }
        else
        {
            if (argument.find_first_not_of("/") != 0)
                return std::nullopt;

            else
                result.input_files.emplace_back(argument);
        }
    }

    if (result.input_files.empty() && !result.show_usage)
    {
        std::cerr << cli::error << "missing operand\n";
        return std::nullopt;
    }

    return result;
}
