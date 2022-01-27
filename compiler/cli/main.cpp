#include <iostream>

#include <fabulist/compiler/compiler.hpp>

#include "console.hpp"

using namespace fabulist::compiler;

int main(int argc, char** argv)
{
    char const* output_location = "fabulist.json";
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
        std::cerr << cli::error << "Parsing " << path << "\n";
        compiler.parse(path);
    }

    compiler.save(output_location);

    return 0;
}
