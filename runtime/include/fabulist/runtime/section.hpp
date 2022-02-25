#ifndef SECTION_HPP
#define SECTION_HPP

#include <memory>
#include <string>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

namespace detail
{

class section;

}

class FABULIST_RUNTIME_EXPORT section
{
    public:
        explicit section();
        ~section() noexcept;
        section(const section&) = delete;
        section& operator=(const section&) = delete;
        section(section&&);
        section& operator=(section&&);


        std::string get_name();

    private:
        std::unique_ptr<detail::section> _pimpl;
};

}

#endif /* SECTION_HPP */
