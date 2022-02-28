#include <iostream>

#include <fabulist/runtime/story.hpp>
#include <fabulist/runtime/version.hpp>

#include "console.hpp"

using namespace fabulist::runtime;

template <typename T>
struct wrap_optional
{
    using type = std::optional<T>;
};

template <typename T>
struct wrap_optional<std::optional<T>>
{
    using type = std::optional<T>;
};

template <typename T>
using wrap_optional_t = typename wrap_optional<T>::type;

template <typename T>
wrap_optional_t<T> get_member(std::optional<cli::parsed_arguments> arguments,
                              T cli::parsed_arguments::*member)
{
    if (!arguments.has_value())
        return std::nullopt;

    return arguments.value().*member;
}

int main(int argc, char const** argv)
{
    auto args = cli::parse_arguments(argc, argv);

    if (args.has_value())
        cli::setup_output(args.value());

    if (get_member(args, &cli::parsed_arguments::show_usage).value_or(true))
    {
        std::cerr << cli::usage;
        return 1;
    }

    if (get_member(args, &cli::parsed_arguments::show_version).value_or(false))
    {
        std::cerr << "Fabulist runtime " << fabulist::runtime::get_version_string() << "\n";
        return 1;
    }

    auto input_file = get_member(args, &cli::parsed_arguments::input_files)
        .value_or(std::vector<std::string>{})
        .at(0);

    auto story = [&input_file]()
    {
        if (input_file[0] == '-')
        {
            std::cerr << cli::verbose << "Parsing from standard input\n";

            return fabulist::runtime::parse_story(std::cin);
        }
        else
        {
            std::filesystem::path story_location{input_file};
            std::cerr << cli::verbose << "Parsing " << story_location << "\n";

            return fabulist::runtime::parse_story(story_location);
        }
    }();

    std::cerr << cli::verbose << "Beginning execution of story at (somewhere)\n";

    return 0;
}
