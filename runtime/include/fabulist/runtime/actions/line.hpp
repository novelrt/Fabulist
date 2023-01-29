#ifndef ACTIONS_LINE_HPP
#define ACTIONS_LINE_HPP

#include <string>
#include <memory>

#include <fabulist/runtime/actions/action.hpp>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime::actions
{

namespace detail
{

struct line;

}

class FABULIST_RUNTIME_EXPORT line : public action
{
    public:
        explicit line(std::string const& speaker, std::string const& text);
        ~line() noexcept override;
        line(const line&) = delete;
        line& operator=(const line&) = delete;
        line(line&&);
        line& operator=(line&&);

        void execute(state& state) const override;
        std::string type() const noexcept override;

        std::string speaker() const noexcept;
        std::string text() const noexcept;

    private:
        std::unique_ptr<detail::line> _pimpl;
};

}

#endif /* ACTIONS_LINE_HPP */
