#ifndef STATE_HPP
#define STATE_HPP

#include <any>
#include <filesystem>
#include <functional>
#include <memory>
#include <ostream>
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

        struct parameters
        {
            size_t version;
            std::function<std::string(std::vector<std::string> const&)> query_callback;
        };

        explicit state(parameters const& params, story const* story, section const* section);
        ~state() noexcept;
        state(const state&) = delete;
        state& operator=(const state&) = delete;
        state(state&&);
        state& operator=(state&&);

        // TODO: is std::any safe here?
        std::any get_variable(std::string variable);

        story const* get_story() const noexcept;
        section const* get_section() const noexcept;

        void jump_to_section(std::string const& section);
        std::vector<std::string>::iterator query(std::vector<std::string>& values) const;

        state_update update();

        void save(std::filesystem::path file);
        void save(std::ostream& stream);

    private:
        bool move_next();
        action const& get_current_action() const noexcept;

        std::unique_ptr<detail::state> _pimpl;

        friend struct state_update;
};

}

#endif /* STATE_HPP */
