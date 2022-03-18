#include <iostream>

#include <getopt.h>

#include "../console.hpp"

std::ostream& cli::detail::usage(std::ostream& stream,
    std::string program_name)
{
    return stream
        << "Usage: " << program_name << " [OPTION]... FILE...\n"
        << "Command line compiler for Fabulist files.\n"
        << "\n"
        << "Arguments:\n"
        << "  FILE                   Fabulist file to compile.\n"
        << "\n"
        << "Options:\n"
        << "  -h, --help             Display this help and exit\n"
        << "  -o, --output=OUTPUT    Output file to save generated story\n"
        << "                         (default: fabulist.json)\n"
        << "  -V, --verbose          Enable verbose mode\n"
        << "  -v, --version          Display compiler version and exit\n";
}


std::optional<cli::parsed_arguments> cli::parse_arguments(
    int argc, char const** argv)
{
    cli::parsed_arguments result{};

    struct option options[] = {
        { "output", optional_argument, nullptr, 'o' },
        { "help", no_argument, nullptr, 'h' },
        { "verbose", no_argument, nullptr, 'V'},
        { "version", no_argument, nullptr, 'v'},
        { nullptr, 0, nullptr, 0}
    };

    cli::detail::set_program_name(argv[0]);

    // why is getopt the way that it is
    char* const* AAAAA = const_cast<char* const*>(argv);

    int longopt_ind = 0;
    while (true)
    {
        int c = getopt_long(argc, AAAAA, "hvVo:", options, &longopt_ind);
        if (c == -1) break;

        switch (c)
        {
            case 'h':
                result.show_usage = true;
                break;

            case 'v':
                result.show_version = true;
                break;

            case 'V':
                result.enable_verbose = true;
                break;

            case 'o':
                result.output_file = optarg;
                break;

            case '?':
                return std::nullopt;
        }
    }

    if (optind >= argc && !(result.show_usage || result.show_version))
    {
        std::cerr << cli::error << "missing operand\n";
        return std::nullopt;
    }
    else
    {
        for (int i = optind; i < argc; i++)
        {
            result.input_files.push_back(argv[i]);
        }
    }

    return result;
}
