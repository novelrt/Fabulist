#ifndef FABULIST_SECTION_HPP
#define FABULIST_SECTION_HPP

#include <filesystem>
#include <istream>
#include <memory>
#include <ostream>
#include <string>

#include "fabulist_compiler_export.hpp"

namespace fabulist::compiler
{

    namespace detail
    {

        class section;

    }

    class FABULIST_COMPILER_EXPORT section
    {
    public:
        explicit section();
        ~section() noexcept;

        section(const section&) = delete;
        section& operator=(const section&) = delete;
        section(section&&);
        section& operator=(section&&);

        std::string name();
        size_t count();

    private:
        std::unique_ptr<detail::section> _pimpl;
    };

}

#endif /* FABULIST_SECTION_HPP */
