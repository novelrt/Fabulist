#ifndef SECTION_HPP
#define SECTION_HPP

#include <memory>
#include <string>
#include <vector>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class action;

namespace detail
{

struct section;

}

class FABULIST_RUNTIME_EXPORT section
{
    public:
        explicit section(std::string const& name,
            std::vector<action>&& actions);
        ~section() noexcept;
        section(const section&) = delete;
        section& operator=(const section&) = delete;
        section(section&&);
        section& operator=(section&&);

        std::string name() const noexcept;

        action const& at(size_t index) const noexcept;
        action const& operator[](size_t index) const noexcept;

        std::vector<action>::const_iterator begin() const noexcept;
        std::vector<action>::const_iterator end() const noexcept;

        size_t size() const noexcept;

    private:
        std::unique_ptr<detail::section> _pimpl;
};

}

#endif /* SECTION_HPP */
