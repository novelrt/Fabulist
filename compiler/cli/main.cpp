#include <iostream>

#include <fabulist/compiler/compiler.hpp>

#include "console.hpp"

using namespace fabulist::compiler;

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

    compiler compiler;

    auto files = get_member(args, &cli::parsed_arguments::input_files)
        .value_or(std::vector<std::string>{});
    for (const auto& file : files)
    {
        std::filesystem::path path{file};
        std::cerr << cli::verbose << "Parsing " << path << "\n";

        try
        {
            compiler.parse(path);
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << "\n";
            std::cerr << cli::error << "compilation halted.\n";
            return 1;
        }
    }

    auto output_file = get_member(args, &cli::parsed_arguments::output_file)
        .value_or("-");
    if (output_file[0] == '-')
    {
        std::cerr << cli::verbose << "Saving to standard output\n";
        compiler.save(std::cout);
        std::cout << '\n';
    }
    else
    {
        std::filesystem::path output{output_file};
        std::cerr << cli::verbose << "Saving to " << output << "\n";
        compiler.save(output);
    }

    return 0;
}
