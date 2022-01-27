#ifndef FABULIST_COMPILER_HPP
#define FABULIST_COMPILER_HPP

#include <filesystem>
#include <istream>
#include <ostream>

#include "fabulist_compiler_export.hpp"

namespace fabulist::compiler
{

class FABULIST_COMPILER_EXPORT compiler
{
    public:
        explicit compiler() = default;
        ~compiler() noexcept = default;

        compiler(const compiler&) = delete;
        compiler& operator=(const compiler&) = delete;
        compiler(compiler&&) = default;
        compiler& operator=(compiler&&) = default;

        void parse(std::filesystem::path path);
        void parse(std::istream& stream);

        void save(std::filesystem::path path);
        void save(std::ostream& stream);
};

}

#endif /* FABULIST_COMPILER_HPP */
