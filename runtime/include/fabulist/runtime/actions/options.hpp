#ifndef ACTIONS_OPTION_HPP
#define ACTIONS_OPTION_HPP

#include <string>
#include <vector>
#include <memory>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/actions/action.hpp>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime::actions
{

namespace detail
{

struct options;

}

struct FABULIST_RUNTIME_EXPORT option
{
    std::string name;
    std::vector<fabulist::runtime::action> actions;
};

class FABULIST_RUNTIME_EXPORT options : public action
{
    public:
        explicit options(std::vector<option>&& options);
        ~options() noexcept override;
        options(const options&) = delete;
        options& operator=(const options&) = delete;
        options(options&&);
        options& operator=(options&&);

        void execute(state& state) const override;
        std::string type() const noexcept override;

        option const& at(std::vector<option>::size_type index) const noexcept;
        option const& operator[](std::vector<option>::size_type index) const noexcept;

        std::vector<option>::const_iterator begin() const noexcept;
        std::vector<option>::const_iterator end() const noexcept;

        std::vector<option>::size_type size() const noexcept;

    private:
        std::unique_ptr<detail::options> _pimpl;
};

}

#endif /* ACTIONS_OPTION_HPP */
