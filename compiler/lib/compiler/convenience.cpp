#include <fstream>

#include <fabulist/compiler/compiler.hpp>

#include "compiler.hpp"

using namespace fabulist::compiler;

void compiler::parse(std::filesystem::path path)
{
    std::ifstream file{path};
    parse(file, "@" + path.string());
}

void compiler::parse(std::istream& stream)
{
    parse(stream, "story");
}

void compiler::save(std::filesystem::path path)
{
    std::ofstream file{path};
    save(file);
}

