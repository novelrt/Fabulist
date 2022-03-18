#include <iostream>
#include <optional>

#include <fabulist/runtime/actions/line.hpp>
#include <fabulist/runtime/actions/options.hpp>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/runtime.hpp>
#include <fabulist/runtime/state.hpp>
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

std::string query_user(std::vector<std::string> const& choices);

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

    runtime runtime{};
    register_default_actions(runtime);

    auto input_file = get_member(args, &cli::parsed_arguments::input_files)
        .value_or(std::vector<std::string>{})
        .at(0);

    auto story = [&input_file,&runtime]()
    {
        if (input_file[0] == '-')
        {
            std::cerr << cli::verbose << "Parsing from standard input\n";

            return runtime.load_story(std::cin, "stdin");
        }
        else
        {
            std::filesystem::path story_location{input_file};
            std::cerr << cli::verbose << "Parsing " << story_location << "\n";

            return runtime.load_story(story_location);
        }
    }();

    auto section = get_member(args, &cli::parsed_arguments::section)
        .value_or("root");

    std::cerr << cli::verbose
        << "Beginning execution of story at " << section << '\n';

    auto state = story.create_state(query_user, section);

    while (true)
    {
        while (auto action = state.update())
        {
            std::cerr << cli::verbose << "Executing " << action->type() << '\n';

            if (action->type() == "line")
            {
                auto line = static_cast<actions::line const*>(**action);
                std::cout << '[' << line->speaker() << "] " << line->text();

                // ignore input but require enter to be pressed
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                action->execute(state);
            }
        }
    }

    return 0;
}

std::string query_user(std::vector<std::string> const& choices)
{
    std::cerr << cli::verbose << "Querying user between " << choices.size() << " options\n";
    size_t index = 0;
    for (auto const& option : choices)
    {
        std::cout << ++index << ". " << option << '\n';
    }

    size_t chosen = 0;
    do
    {
        std::cout << "> ";
        std::cin >> chosen;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (chosen <= 0 || chosen > index)
        {
            std::cout << "Invalid choice (between 1 and " << index << ")\n";
        }
    }
    while (chosen <= 0 || chosen > index);

    std::cerr << cli::verbose << "Selected option " << chosen << '\n';

    return choices.at(chosen - 1);
}
