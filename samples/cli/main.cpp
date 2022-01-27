#include <fstream>
#include <functional>
#include <getopt.h>
#include <iostream>

#include <fabulist/story.hpp>

char const* program;

std::ostream& usage(std::ostream& stream)
{
    return stream
        << "Usage: " << program << " [OPTION]... FILE\n"
        << "Command line execution environment for Fabulist files.\n"
        << "\n"
        << "Arguments:\n"
        << "  FILE                     Fabulist file to execute.\n"
        << "\n"
        << "Options:\n"
        << "  -h, --help               Display this help and exit\n"
        << "  -s, --section[=SECTION]  Section to begin execution at\n"
        << "                           (default: root)\n";
}

static struct option options[] = {
    { "section", optional_argument, NULL, 's' },
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0}
};

bool parseargs(int argc, char** argv,
    char const** section,
    char const** file)
{
    int longopt_ind = 0;
    while (true)
    {
        int c = getopt_long(argc, argv, "s::h", options, &longopt_ind);
        if (c == -1) break;

        switch (c)
        {
            case 's':
                *section = optarg;
                break;
            case 'h':
            case '?':
                return false;
        }
    }

    if (optind >= argc)
    {
        std::cerr << program << ": missing operand\n";
        return false;
    }
    else if ((argc - optind) > 1)
    {
        std::cerr << program << ": too many operands\n";
        return false;
    }
    else
    {
        *file = argv[optind];
    }

    return true;
}

int main(int argc, char** argv)
{
    program = argv[0];

    char const* section = "root";
    char const* story_file_location;
    if (!parseargs(argc, argv, &section, &story_file_location))
    {
        std::cerr << usage;
        return 1;
    }

    std::ifstream story_file{story_file_location};

    if (!story_file.is_open())
    {
        std::cerr << program << ": failed to open "
            << story_file_location << "\n";
        return 2;
    }

    fabulist::story story = fabulist::load_story_from_stream(story_file);

    return 0;
}
