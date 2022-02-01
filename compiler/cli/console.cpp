#include <getopt.h>
#include <iostream>

#include "console.hpp"

// A dummy ostream used to disable verbose output if the flag isn't set
class null_ostream : public std::ostream
{ };

static char const* program;
static int enable_verbose = 0;
static null_ostream null_output;

std::ostream& cli::error(std::ostream& stream)
{
    return stream << program << ": ";
}

std::ostream& cli::verbose(std::ostream& stream)
{
    if (!enable_verbose)
    {
        return null_output;
    }
    else
    {
        return stream;
    }
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
        << "                           (default: fabulist.json)\n"
        << "  -v, --verbose            Enable verbose mode\n";
}

static struct option options[] = {
    { "output", optional_argument, NULL, 'o' },
    { "help", no_argument, NULL, 'h' },
    { "verbose", no_argument, &enable_verbose, 'v'},
    { NULL, 0, NULL, 0}
};

bool cli::parseargs(int argc, char** argv, char const** output, int* file_list)
{
    program = argv[0];

    int longopt_ind = 0;
    while (true)
    {
        int c = getopt_long(argc, argv, "ho::v", options, &longopt_ind);
        if (c == -1) break;

        switch (c)
        {
            case 'h':
            case '?':
                return false;
            case 'o':
                *output = optarg;
                break;
            case 'v':
                enable_verbose = 1;
                break;
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
