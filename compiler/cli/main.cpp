#include <iostream>

#include <fabulist/compiler/compiler.hpp>

#include "console.hpp"

using namespace fabulist::compiler;

int main(int argc, char** argv)
{
    char const* output_location = "-";
    int file_idx;
    if (!cli::parseargs(argc, argv, &output_location, &file_idx))
    {
        std::cerr << cli::usage;
        return 1;
    }

    compiler compiler;

    for (int i = file_idx; i < argc; i++)
    {
        std::filesystem::path path{argv[i]};
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

    if (*output_location == '-')
    {
        compiler.save(std::cout);
    }
    else
    {
        std::filesystem::path output{output_location};
        std::cerr << cli::verbose << "Saving to " << output << "\n";
        compiler.save(output);
    }

    return 0;
}
