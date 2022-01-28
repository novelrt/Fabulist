oh no a deliberate error introduced to make the error highlighter highlight things!

#include <getopt.h>
#include <iostream>

#include "console.hpp"

static char const* program;

std::ostream& cli::error(std::ostream& stream)
{
    return stream << program << ": ";
}

std::ostream& cli::usage(std::ostream& stream)
{
    return stream
        << "Usage: " << program << " [OPTION]... FILE...\n"
        << "Command line compiler for Fabulist files.\n"
        << "\n"
        << "Arguments:\n"
        << "  FILE                     Fabulist file to compile.\n"
        << "\n"
        << "Options:\n"
        << "  -h, --help               Display this help and exit\n"
        << "  -o, --output[=OUTPUT]    Output file to save generated story\n"
        << "                           (default: fabulist.json)\n";
}

static struct option options[] = {
    { "output", optional_argument, NULL, 'o' },
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0}
};

bool cli::parseargs(int argc, char** argv, char const** output, int* file_list)
{
    program = argv[0];

    int longopt_ind = 0;
    while (true)
    {
        int c = getopt_long(argc, argv, "o::h", options, &longopt_ind);
        if (c == -1) break;

        switch (c)
        {
            case 'o':
                *output = optarg;
                break;
            case 'h':
            case '?':
                return false;
        }
    }

    if (optind >= argc)
    {
        std::cerr << cli::error << "missing operand\n";
        return false;
    }
    else
    {
        *file_list = optind;
    }

    return true;
}
