#ifndef ACTIONS_CALL_HPP
#define ACTIONS_CALL_HPP

#include <string>
#include <memory>
#include <vector>

#include <fabulist/runtime/actions/action.hpp>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime::actions
{

    namespace detail
    {

        struct call;

    }

    class FABULIST_RUNTIME_EXPORT call : public action
    {
    public:
        explicit call(std::string const& section, std::vector<std::string> parameters);
        ~call() noexcept override;
        call(const call&) = delete;
        call& operator=(const call&) = delete;
        call(call&&);
        call& operator=(call&&);

        void execute(state& state) const override;
        std::string type() const noexcept override;

        std::string method() const noexcept;

    private:
        std::unique_ptr<detail::call> _pimpl;
    };

}

#endif /* ACTIONS_CALL_HPP */

