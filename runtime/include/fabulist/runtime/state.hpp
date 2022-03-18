#ifndef STATE_HPP
#define STATE_HPP

#include <any>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class action;
class section;
class story;

namespace detail
{

struct state;

}

class FABULIST_RUNTIME_EXPORT state
{
    public:
        using query_callback_type = std::function<std::string(std::vector<std::string> const&)>;

        struct state_update
        {
            ~state_update() noexcept = default;
            state_update(const state_update&) = delete;
            state_update& operator=(const state_update&) = delete;
            state_update(state_update&&) = delete;
            state_update& operator=(state_update&&) = delete;

            operator bool() const noexcept;
            operator action const&() const noexcept;

            action const& operator*() const noexcept;
            action const& operator->() const noexcept;

            private:
                explicit state_update(state* state)
                    : _state{state}
                { };

                state* _state;

                friend class state;
        };

        explicit state(query_callback_type query_callback, story const* story, section const* section);
        ~state() noexcept;
        state(const state&) = delete;
        state& operator=(const state&) = delete;
        state(state&&);
        state& operator=(state&&);

        // TODO: is std::any safe here?
        std::any get_variable(std::string variable);

        story const* story() const noexcept;
        section const* section() const noexcept;

        void jump_to_section(std::string const& section);
        std::vector<std::string>::iterator query(std::vector<std::string>& values) const;

        state_update update();

    private:
        bool move_next();
        action const& get_current_action() const noexcept;

        std::unique_ptr<detail::state> _pimpl;

        friend struct state_update;
};

}

#endif /* STATE_HPP */
