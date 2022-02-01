#ifndef FABULIST_COMPILER_HPP
#define FABULIST_COMPILER_HPP

#include <filesystem>
#include <istream>
#include <memory>
#include <ostream>

#include "fabulist_compiler_export.hpp"

namespace fabulist::compiler
{

namespace detail
{

class compiler;

}

class FABULIST_COMPILER_EXPORT compiler
{
    public:
        explicit compiler();
        ~compiler() noexcept;

        compiler(const compiler&) = delete;
        compiler& operator=(const compiler&) = delete;
        compiler(compiler&&);
        compiler& operator=(compiler&&);

        void parse(std::filesystem::path path);
        void parse(std::istream& stream);
        void parse(std::istream& stream, std::string name);

        void save(std::filesystem::path path);
        void save(std::ostream& stream);
    private:
        std::unique_ptr<detail::compiler> _pimpl;
};

}

#endif /* FABULIST_COMPILER_HPP */
