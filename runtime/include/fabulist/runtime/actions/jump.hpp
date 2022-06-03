#ifndef ACTIONS_JUMP_HPP
#define ACTIONS_JUMP_HPP

#include <string>
#include <memory>

#include <fabulist/runtime/actions/action.hpp>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime::actions
{

namespace detail
{

struct jump;

}

class FABULIST_RUNTIME_EXPORT jump : public action
{
    public:
        explicit jump(std::string const& section);
        ~jump() noexcept override;
        jump(const jump&) = delete;
        jump& operator=(const jump&) = delete;
        jump(jump&&);
        jump& operator=(jump&&);

        void execute(state& state) const override;
        std::string type() const noexcept override;

        std::string section() const noexcept;

    private:
        std::unique_ptr<detail::jump> _pimpl;
};

}

#endif /* ACTIONS_JUMP_HPP */
